/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** FutureTasking
*/

#ifndef FutureTasking_hpp
	#define FutureTasking_hpp

# include <iostream>
# include <vector>
# include <Task.hpp>

template<typename T>
class FutureTasking
{
public:
	FutureTasking()
	{
	}

	void addTask(T * job)
	{
		this->jobs.push_back(job);
	}

	void operator=(T * job)
	{
		this->addTask(job);
	}

	void operator+=(T * job)
	{
		this->addTask(job);
	}

	~FutureTasking()
	{
		for (auto &job : this->jobs)
			job->getTask();
	}
private:
	std::vector<T*> jobs;
};

#endif /* FutureTasking_hpp */
