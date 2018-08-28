/*
** EPITECH PROJECT, 2018
** Information
** File description:
** Implementation of Information
*/

#include <iostream>
#include <regex>
# include <sstream>
#include "Information.hpp"

Information::Information(Command command) : command(command)
{
	switch (command.getType())
	{
		case EMAIL_ADDRESS:
			regex = std::regex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\."
		"(\\w+))+");
			break;
		case PHONE_NUMBER:
			regex = std::regex("(33|0)(6|7|9)\\d{8}");
			break;
		case IP_ADDRESS:
			regex = std::regex("(\\d{1,3}(\\.\\d{1,3}){3})");
			break;
		default:
			break;
	}
}

Information::~Information()
{

}

const std::vector<std::string> &Information::getFiles() const
{
	return this->command.getFilenames();
}

Type Information::getType() const
{
	return this->command.getType();
}

const std::regex &Information::getRegex() const
{
	return this->regex;
}

const std::vector<std::string> &Information::getData() const
{
	return data;
}

std::string &operator<<(std::string &os, const std::vector<std::string> datas)
{
	for (const std::string &content : datas)
		os += content + SEPARATOR;
	return os;
}

void operator>>(std::string &os,
				     std::vector<std::string> &datas)
{
	std::string tmp;
	std::stringstream str(os);

	while (std::getline(str, tmp, SEPARATOR))
		datas.push_back(tmp);
}
