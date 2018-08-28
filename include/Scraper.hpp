/*
** EPITECH PROJECT, 2018
** Scraper
** File description:
** Declaration of Scraper
*/

#ifndef NANOTEKSPICE_SCRAPER_HPP
	#define NANOTEKSPICE_SCRAPER_HPP

#include <regex>
#include <fstream>
#include <exception>
#include <string>
#include <vector>
#include "Information.hpp"

class Scraper
{
public:
	explicit Scraper(Information &info);
	void parseAll();
	const std::vector<std::string> &getResult() const;
	void checkFiles();
	virtual ~Scraper();
private:
	void parseByFile(std::string file);
private:
	Information info;
	std::vector<std::string> result;
};

#endif //NANOTEKSPICE_SCRAPER_HPP
