/*
** EPITECH PROJECT, 2018
** Information
** File description:
** Declaration of Information
*/

#ifndef NANOTEKSPICE_INFORMATION_HPP
	#define NANOTEKSPICE_INFORMATION_HPP

#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include "Command.hpp"
#include "Type.hpp"

#define SEPARATOR ';'

class Information
{
public:
	Information(Command command);
	const std::vector<std::string> &getFiles() const;
	Type getType() const;
	const std::regex &getRegex() const;
	const std::vector<std::string> &getData() const;
	void setData(const std::vector<std::string> &rawData);
	void addData(const std::string &data);
	void displayRawData() const;
	virtual ~Information();
private:
	Command command;
	std::regex regex;
	std::vector<std::string> data;
};

std::string &operator<<(std::string &os, const std::vector<std::string> datas);
void operator>>(std::string &os, std::vector<std::string> &datas);

#endif //NANOTEKSPICE_INFORMATION_HPP
