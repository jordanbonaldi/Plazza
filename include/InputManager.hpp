/*
** EPITECH PROJECT, 2018
** InputManager
** File description:
** Create class
*/

#ifndef CPP_PLAZZA_INPUTMANAGER_HPP
#define CPP_PLAZZA_INPUTMANAGER_HPP

#include "ThreadPool.hpp"
#include "Input.hpp"
#include "SlaveManager.hpp"

class InputManager
{
public:
	virtual ~InputManager();

public:
	InputManager(size_t threads, int);
	SlaveManager getSlaveManager();
	void build();

private:
	Input input;
	SlaveManager svm;
};

#endif //CPP_PLAZZA_INPUTMANAGER_HPP
