/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** ThreadPool
*/

#ifndef ThreadPool_hpp
	#define ThreadPool_hpp

# include <iostream>
# include <type_traits>
# include <utility>
# include <cstdint>
# include <algorithm>
# include <functional>
# include "Thread.hpp"
# include "SafeQueue.hpp"
# include "Executor.hpp"
# include "Task.hpp"
# include "FutureTasking.hpp"

# define _Job std::function<void()>
# define _T Thread<_Job>

class ThreadPool
{
public:
	inline ThreadPool(size_t threads = 1)
	{
		this->threads_count = threads;
		this->create();
	}

	template<class ... Func>
	void launchActions(Func && ... f)
	{
		{
			FutureTasking<Task<void>> tasking;
			std::vector<std::function<Task<void> *()>> funcs = {f...};
			for (auto &a : funcs)
				tasking = a();
		}
	}

	template<class F, typename... Args>
	auto addJob(F && job, Args && ... args)
	{
		auto task = std::bind(std::forward<F>(job), std::forward<Args>(args)...);

		using _result = std::result_of_t<decltype(task)()>;
		using _packaged = std::packaged_task<_result()>;
		using _type = Executor<_packaged>;

		_packaged formated_task{std::move(task)};
		Task<_result> *result = new Task<_result>();
		result->addTask(formated_task.get_future());
		this->worker_queue.push(std::make_unique<_type>(std::move(formated_task)));
		return result;
	}

	bool isDone()
	{
		for (auto &a : this->threads)
			if (a.getStatus() != "DEAD")
				return false;
		return true;
	}

	int getSizeQueue()
	{
		return this->worker_queue.size();
	}

	inline ~ThreadPool()
	{
		this->remove();
	}

private:
	void create()
	{
		try {
			for (size_t i = 0; i < this->threads_count; i++)
				this->threads.emplace_back(_T()
				.action([&](){
					this->slaveWork();
				}).run());
		} catch (...) {
			this->remove();
			throw;
		}
	}

	void slaveWork()
	{
		while (!this->finished) {
			std::unique_ptr<IExecutor> executor{nullptr};
			if (this->worker_queue.waitPop(executor))
				executor->run();
		}
	}

	void remove()
	{
		this->finished = true;
		this->worker_queue.destroy();
		for (auto &thread : this->threads)
			if (thread.isJoinable())
				thread.join();
	}



private:
	std::atomic_bool finished{false};
	SafeQueue<std::unique_ptr<IExecutor>> worker_queue;
	std::vector<_T> threads;
	size_t threads_count;
};

#endif /* ThreadPool_hpp */
