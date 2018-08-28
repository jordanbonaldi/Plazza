/*
** EPITECH PROJECT, 2018
** Input
** File description:
** Declaration of Input
*/

#ifndef Input_HPP
	#define Input_HPP

#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <queue>
#include "Command.hpp"

class Input {
public:
	explicit Input();
	Input &addDelimiter(char);
	std::string getNextCommand();
	virtual ~Input();
private:
	void split(const std::string &s, char delim);
	std::string cleanString(const std::string &input);
	std::string removeAroundSpaces(const std::string &str);
	std::queue<std::string> waitingCommandStrings;
	char commandSeparator;
};

#endif /* Input_HPP */
