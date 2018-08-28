/*
** EPITECH PROJECT, 2018
** InputManager
** File description:
** Create class
*/

#ifndef CPP_PLAZZA_SLAVEMANAGER_HPP
	#define CPP_PLAZZA_SLAVEMANAGER_HPP

#include <map>
#include "Information.hpp"
#include "Slave.hpp"
#include "SocketClient.hpp"

class SlaveManager
{

public:
	SlaveManager(size_t size, int mainport)
	{
		this->size = size;
		server.create();
		this->mainport = mainport;
	}

	int getSlaveAvailable()
	{
		int i = 0;

		for (auto &a : this->slaves) {
			std::string rcv;
			server.sendMessage("FULL\n", a);
			while ((rcv = server.receiveMessage(a)).empty());
			if (rcv == "NO")
				return i;
			else if (!rcv.compare(0, 4, "EXIT")) {
				this->removeSlave(i);
				return getSlaveAvailable();
			}
			i++;
		}
		return -1;
	}

	void removeSlave(int index)
	{
		this->slaves.erase(this->slaves.begin() + index);
	}

	int getSlaves()
	{
		return this->slaves.size();
	}

	bool isDone()
	{
		this->getSlaveAvailable();
		return this->slaves.size() == 0;
	}

	void createSlave(Scraper &scrap, std::string line)
	{
		int index = 0;
		int conn = 0;

		if (this->slaves.size() > 0) {
			index = this->getSlaveAvailable();
			if (index >= 0) {
				this->sendCommand(index, line);
				return;
			}
		}
		if (!fork()) {
			Slave sv(this->size, server.getPort(), this->mainport);
			sv.addJobs(scrap);
			while (sv.getType() != Slave::DEAD)
				sv.receiveMessage();
			exit(0);
		} else {
			conn = server.connection();
			this->slaves.push_back(conn);
		}
	}

	void sendCommand(size_t id, std::string line)
	{
		server.sendMessage(line + "\n", this->slaves.at(id));
	}

private:
	size_t size;
	std::vector<int> slaves;
	int mainport;

private:
	SocketServer server;
};

#endif //CPP_PLAZZA_SLAVEMANAGER_HPP
