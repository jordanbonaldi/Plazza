/*
** EPITECH PROJECT, 2018
** Command
** File description:
** Implementation of Command
*/

#include "Command.hpp"

Command::Command(const std::string &command) : command(command)
{
	types = {
		{"IP_ADDRESS", Type::IP_ADDRESS},
		{"EMAIL_ADDRESS", Type::EMAIL_ADDRESS},
		{"PHONE_NUMBER", Type::PHONE_NUMBER},
	};
}

std::vector<std::string> Command::split(const std::string &s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> strings;

	while(std::getline(ss, item, delim)) {
		strings.push_back(item);
	}
	if (!ss.eof()) {
		std::getline(ss, item, delim);
		strings.push_back(item);
	}
	return strings;
}

void Command::parseCommand()
{
	std::vector<std::string> strings = split(command, ' ');

	if (strings.size() < 2)
		exit(84);
	if (types.count(strings.back()))
		type = types[strings.back()];
	else
		exit(84);
	filenames = strings;
	filenames.pop_back();
}

const std::vector<std::string> &Command::getFilenames() const
{
	return filenames;
}

Type Command::getType() const
{
	return type;
}
