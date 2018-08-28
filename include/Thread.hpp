/*
** EPITECH PROJECT, 2018
** cpp_plazza
** File description:
** Thread
*/

#ifndef Thread_hpp
	#define Thread_hpp

# include <iostream>
# include <thread>
# include <vector>
# include "IThread.hpp"

template<class C>
class Thread : public IThread<C>
{
public:
	Thread()
	{
		this->status = NONE;
	}

	Thread &action(C function) final
	{
		this->function = [function, this](){
			this->status = RUNNING;

			function();

			this->status = DEAD;
		};
		return *this;
	}

	bool isJoinable() const final
	{
		return this->thread->joinable();
	}

	Thread &run() final
	{
		this->status = STARTED;
		this->thread = new std::thread(this->function);
		//this->thread->detach();
		return *this;
	}

	Thread &join() final
	{
		this->thread->join();
		return *this;
	}

	std::string getStatus() const
	{
		switch (status)
		{
			case STARTED:
				return "STARTED";
			case RUNNING:
				return "RUNNING";
			case DEAD:
				return "DEAD";
			case NONE:
				return "NONE";
			default:
				return "Error";
		}
	}

	~Thread() {};
private:
	enum Status {
		STARTED,
		RUNNING,
		DEAD,
		NONE,
	};
	std::thread *thread;
	C function;
	Status status;
};

#endif /* Thread_hpp */
