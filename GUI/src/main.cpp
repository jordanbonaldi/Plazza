/*
** EPITECH PROJECT, 2018
** main.cpp
** File description:
** main
*/

#include "MainWindow.hpp"
#include "ThreadPool.hpp"

int main(int ac, char **av)
{
	if (ac != 2) {
		dprintf(2, "Invalid arguments.\n");
		return (84);
	}
	MainWindow window = MainWindow(std::string(av[1]));
	window.display();
	return (0);
}