/*
** EPITECH PROJECT, 2018
** MainWindow.cpp
** File description:
** MainWindow class implementation
*/

#include "MainWindow.hpp"

MainWindow::MainWindow(const std::string &av)
{
	int init = 0;
	app = new QApplication(init, NULL);
	window = new QMainWindow();
	QWidget *mainWidget = new InputManagerWidget(std::stoi(av));

	window->setCentralWidget(mainWidget);
	window->resize(600, 400);
	window->show();
}

void MainWindow::display()
{
	app->exec();
}