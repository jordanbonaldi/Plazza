/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Task
*/

#ifndef Task_hpp
	#define Task_hpp

# include <iostream>
# include <future>

template<typename T>
class Task
{
public:
	Task()
	{
	}

	// Task(const Task& rhs) = delete;
	// Task& operator=(const Task& rhs) = delete;
	// Task(Task&& other) = default;
	// Task& operator=(Task&& other) = default;

	void addTask(std::future<T> && task)
	{
		this->future_task = std::move(task);
	}

	auto getTask()
	{
		if (this->future_task.valid())
			return this->future_task.get();
		return;
	}

	~Task()
	{
		if (this->future_task.valid())
			this->future_task.get();
	}
private:
	std::future<T> future_task;
};

#endif /* Task_hpp */
