/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Executor
*/

#ifndef Executor_hpp
	#define Executor_hpp

# include "IExecutor.hpp"

template<class U>
class Executor : public IExecutor
{
public:
	Executor(U && future) : executor(std::move(future))
	{
	}

	Executor(const Executor& rhs) = delete;
	Executor& operator=(const Executor& rhs) = delete;
	Executor(Executor && other) = default;
	Executor& operator=(Executor && other) = default;

	void addExecutor(U && executor)
	{
		this->executor = std::move(executor);
	}

	void run() final
	{
		//std::cout << "executing" << std::endl;
		this->executor();
	}
private:
	U executor;
};

#endif /* Executor_hpp */
