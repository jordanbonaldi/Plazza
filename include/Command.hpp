/*
** EPITECH PROJECT, 2018
** Command
** File description:
** Declaration of Command
*/

#ifndef NANOTEKSPICE_COMMAND_HPP
	#define NANOTEKSPICE_COMMAND_HPP

#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>
#include <exception>
#include "Type.hpp"

class Command
{
public:
	explicit Command(const std::string &command);
	void parseCommand();

	const std::vector<std::string> &getFilenames() const;

	Type getType() const;

private:
	std::vector<std::string> split(
		const std::string &s, char delim);
	std::string command;
	std::vector<std::string> filenames;
	Type type;
	std::map<std::string, Type> types;
};

#endif //NANOTEKSPICE_COMMAND_HPP
