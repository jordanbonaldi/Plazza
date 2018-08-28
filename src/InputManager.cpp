/*
** EPITECH PROJECT, 2018
** InputManager
** File description:
** Create class
*/

#include <Scraper.hpp>
#include "InputManager.hpp"

InputManager::InputManager(size_t threads, int mainport) : svm(SlaveManager
								  (threads,
								   mainport))
{
	this->input.addDelimiter(';');
}

InputManager::~InputManager()
{
}

void InputManager::build()
{
	bool finished = false;
	std::string line;

	while (!finished) {
		line = this->input.getNextCommand();
		if (line.empty())
			break;
		Command m(line);
		m.parseCommand();
		Information info(m);
		Scraper scraper(info);
		scraper.checkFiles();
		svm.createSlave(scraper, line);
		if (line == "END")
			finished = true;
	}
}

SlaveManager InputManager::getSlaveManager()
{
	return this->svm;
}