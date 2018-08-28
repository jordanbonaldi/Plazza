/*
** EPITECH PROJECT, 2018
** MainWindow.hpp
** File description:
** MainWindow header file
*/

#ifndef MAINWINDOW_HPP_
	#define MAINWINDOW_HPP_

#include <QtCore/QtCore>
#include <QtWidgets/QApplication>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QInputDialog>
#include "InputManagerWidget.hpp"

class MainWindow
{
	public:
		MainWindow(const std::string &av);
		void display();

	private:
		QApplication *app;
		QMainWindow *window;
};

#endif /* !MAINWINDOW_HPP_ */
