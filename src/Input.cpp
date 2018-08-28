/*
** EPITECH PROJECT, 2018
** Input
** File description:
** Implementation of Input
*/

#include "Input.hpp"

Input::Input()
{
}

void Input::split(const std::string &s, char delim)
{
	std::stringstream ss(s);
	std::string item;

	while(std::getline(ss, item, delim)) {
		waitingCommandStrings.push(item);
	}
	if (!ss.eof()) {
		std::getline(ss, item, delim);
		waitingCommandStrings.push(item);
	}
}

std::string Input::removeAroundSpaces(const std::string &str)
{
	const auto strBegin = str.find_first_not_of(' ');
	if (strBegin == std::string::npos)
		return "";
	const auto strEnd = str.find_last_not_of(' ');
	const auto strRange = strEnd - strBegin + 1;
	return str.substr(strBegin, strRange);
}

std::string Input::cleanString(const std::string &input)
{
	std::string output = "";

	std::unique_copy(input.begin(),
			input.end(),
			std::back_insert_iterator<std::string>(output), [](char a,char b)
	{
		return isspace(a) && isspace(b);
	});
	return output;
}

std::string Input::getNextCommand()
{
	std::string tmp = "";
	std::string line = "";

	if (!waitingCommandStrings.empty()) {
		line = waitingCommandStrings.front();
		waitingCommandStrings.pop();
	}
	else {
		getline(std::cin, tmp);
		if (tmp.find(commandSeparator) != std::string::npos) {
			split(tmp, commandSeparator);
			return getNextCommand();
		}
		else
			line = tmp;
	}
	std::for_each(line.begin(), line.end(), [](char &c){
		if (c == '\t')
			c = ' ';
	});
	line = removeAroundSpaces(line);
	line = cleanString(line);
	return line;
}

Input::~Input()
{

}

Input &Input::addDelimiter(char delimiter)
{
	this->commandSeparator = delimiter;
	return *this;
}
