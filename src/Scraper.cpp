/*
** EPITECH PROJECT, 2018
** Scraper
** File description:
** Implementation of Scraper
*/

#include <iostream>
#include "Scraper.hpp"

Scraper::Scraper(Information &info) : info(info)
{
}

Scraper::~Scraper()
{
}

void Scraper::parseByFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
		exit(84);
	std::string fileContent(std::istreambuf_iterator<char>(file.rdbuf()),
				std::istreambuf_iterator<char>());
	std::sregex_iterator iter(fileContent.begin(), fileContent.end(),
				  this->info.getRegex());
	std::sregex_iterator end;

	while(iter != end)
	{
		result.push_back((*iter)[0]);
		++iter;
	}
	file.close();
}

const std::vector<std::string> &Scraper::getResult() const
{
	return result;
}

void Scraper::parseAll()
{
	for (auto &a : this->info.getFiles()) {
		this->parseByFile(a);
	}
}

void Scraper::checkFiles()
{
	for (auto &a : this->info.getFiles()) {
		std::ifstream file(a);
		if (!file.is_open())
			exit(84);
		file.close();
	}
}
