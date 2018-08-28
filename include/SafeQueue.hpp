/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** SafeQueue
*/

#ifndef SafeQueue_hpp
	#define SafeQueue_hpp

# include <atomic>
# include <mutex>
# include <queue>
# include <utility>
# include <condition_variable>
# include "ISafeQueue.hpp"

# define _m std::mutex
# define _M std::lock_guard<_m> lock(this->mutex)
# define _UM std::unique_lock<_m> lock(this->mutex)

template<typename U>
class SafeQueue : public ISafeQueue<U>
{
public:
	SafeQueue() {}

	void push(U u)
	{
		_M;

		this->queue.push(std::move(u));
		this->cond.notify_one();
	}

	U pop() final
	{
		U i;
		_UM;

		while (this->queue.empty()) {
			this->cond.wait(lock);
		}
		i = std::move(this->queue.front());
		this->queue.pop();
		return i;
	}

	bool tryPop(U &u) final
	{
		_M;

		if (this->empty() || !this->validate)
			return false;
		u = std::move(this->queue.front());
		this->queue.pop();
		return true;
	}

	bool waitPop(U &u) final
	{
		_UM;

		this->cond.wait(lock, [this]()
		{
			return !this->queue.empty() || !this->validate;
		});

		if (!this->validate)
			return false;
		u = std::move(this->queue.front());
		this->queue.pop();
		return true;
	}

	void clear() final
	{
		_M;

		while (!this->queue.empty())
			this->queue.pop();
		this->cond.notify_all();
	}

	int size()
	{
		_M;

		return this->queue.size();
	}

	bool empty() const final
	{
		_M;

		return this->queue.empty();
	}

	bool isValidate() const final
	{
		_M;

		return this->validate;
	}

	void destroy() final
	{
		_M;

		this->validate = false;
		this->cond.notify_all();
	}

	~SafeQueue()
	{
		this->destroy();
	}
private:
	std::atomic_bool validate{true};
	std::queue<U> queue;
	mutable std::mutex mutex;
	std::condition_variable cond;
};

#endif /* SafeQueue_hpp */
