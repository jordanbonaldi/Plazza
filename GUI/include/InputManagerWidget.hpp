/*
** EPITECH PROJECT, 2018
** InputManagerWidget.hpp
** File description:
** InputManagerWidget header file
*/

#ifndef INPUTMANAGERWIDGET_HPP_
	#define INPUTMANAGERWIDGET_HPP_

#include <QtCore/QtCore>
#include <QtWidgets/QApplication>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QInputDialog>
#include <iostream>
#include <fstream>
#include <vector>
#include "SlaveManager.hpp"
#include "SocketServer.hpp"

class InputManagerWidget : public QWidget
{
Q_OBJECT
public:
	InputManagerWidget(const size_t size);
	virtual ~InputManagerWidget() {};
	void initMainLayout();
	void executeInstruction(const unsigned int infoIndex);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);

private slots:
	void choosePath();
	void executeInstructions();
	void refreshUI();

private:
	std::vector<std::pair<std::string, int>> history;
	QLineEdit *path;
	QTextEdit *monitoring;
	QPushButton *choosePathButton;
	QRadioButton *checkBox1;
	QRadioButton *checkBox2;
	QRadioButton *checkBox3;
	QPushButton *executeButton;
	QTimer *refresh;
	SlaveManager *svm;
	SocketServer server;
	bool initialized;
};

#endif /* !INPUTMANAGERWIDGET_HPP_ */
