/*
** EPITECH PROJECT, 2018
** Slave
** File description:
** Create class
*/

#ifndef CPP_PLAZZA_SLAVE_HPP
#define CPP_PLAZZA_SLAVE_HPP

#include <cstdio>
# include <chrono>
#include "ThreadPool.hpp"
# include "Scraper.hpp"
#include "SocketServer.hpp"
#include "SocketClient.hpp"

class Slave
{
public:

	enum SlaveType
	{
		RUNNING,
		FULL,
		DEAD
	};

	Slave(size_t size, int port, int mainport) : client("127.0.0.1", port)
	{
		this->size = size;
		this->type = RUNNING;
		this->threads_number = 0;
		this->mainport = mainport;

		this->client.create();
		this->client.connection();
		pool = new ThreadPool(size);
		this->timeold = std::chrono::system_clock::now();
		Thread<std::function<void()>>().action([&](){
			while (true) {
				auto time = std::chrono::system_clock::now();
				if (getElapsedTime(time) >= 5 && this->done
					()) {
					std::string rcv;
					client.sendMessage("EXIT\n");
					exit(1);
				}
				sleep(1);
			}
		}).run();
	}

	void addCommandJob(std::string string)
	{
		std::string line = string;
		Command m(line);
		m.parseCommand();
		Information info(m);
		Scraper scrap(info);
		this->addJobs(scrap);
	}

	int getElapsedTime(std::chrono::system_clock::time_point time)
	{
		std::chrono::duration<double> elapsed_sec =
			time - this->timeold;
		return elapsed_sec.count();
	}

	bool done()
	{
		for (auto &a : finished) {
			if (!a.second)
				return false;
		}
		return true;
	}

	void receiveMessage()
	{
		std::string received;

		while ((received = this->client.receiveMessage()).empty());
		if (received == "FULL") {
			this->type = (threads_number >= (int)(2 * size)) ?
				     FULL : RUNNING;
			this->client.sendMessage(this->type == RUNNING ?
						 "NO\n" : "YES\n");
			return;
		}
		this->timeold = std::chrono::system_clock::now();
		this->addCommandJob(received);
	}

	void addJobs(Scraper &scrap){
		this->threads_number ++;
		finished[this->threads_number] = false;
		this->pool->addJob([&](Scraper &scraper){
			SocketClient client_local("127.0.0.1", this->mainport);
			std::string result("");

			scraper.parseAll();
			result << scraper.getResult();
			client_local.create();
			client_local.connection();
			client_local.sendMessage(
				"DONE@" + result + "\n");
			client_local.disconnection();
			finished[threads_number] = true;
			threads_number --;
		}, scrap);
	}

	virtual ~Slave()
	{
		exit(EXIT_SUCCESS);
	}

	SlaveType getType() const
	{
		return type;
	}


private:
	ThreadPool *pool;
	SlaveType type;
	size_t size;
	int threads_number;
	int mainport;
	SocketClient client;
	std::map<int, bool> finished;
	std::chrono::system_clock::time_point timeold;
};

#endif //CPP_PLAZZA_SLAVE_HPP
