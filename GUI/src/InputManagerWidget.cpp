/*
** EPITECH PROJECT, 2018
** InputManagerWidget.cpp
** File description:
** InputManagerWidget class implementation
*/

#include "InputManagerWidget.hpp"
#include "InputManagerWidget.moc"

void InputManagerWidget::initMainLayout()
{
	QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
	QBoxLayout *pathLayout = new QBoxLayout(QBoxLayout::LeftToRight);
	QBoxLayout *selectionLayout = new QBoxLayout(QBoxLayout::LeftToRight);

	pathLayout->addWidget(path);
	pathLayout->addWidget(choosePathButton);
	selectionLayout->addWidget(checkBox1);
	selectionLayout->addWidget(checkBox2);
	selectionLayout->addWidget(checkBox3);
	layout->addLayout(pathLayout);
	layout->addLayout(selectionLayout);
	layout->addWidget(executeButton);
	layout->addWidget(monitoring);
	setLayout(layout);
}

InputManagerWidget::InputManagerWidget(const size_t size) : QWidget()
{
	initialized = false;
	path = new QLineEdit("No path selected");
	choosePathButton = new QPushButton("Choose path");
	executeButton = new QPushButton("Launch program");
	checkBox1 = new QRadioButton("Email address");
	checkBox2 = new QRadioButton("Phone number");
	checkBox3 = new QRadioButton("IP address");
	monitoring = new QTextEdit();
	server.create();
	svm = new SlaveManager(size, server.getPort());
	refresh = new QTimer(this);
	monitoring->setReadOnly(true);
	initMainLayout();
	connect(choosePathButton, SIGNAL(released()), this,
						SLOT(choosePath()));
	connect(executeButton, SIGNAL(released()), this,
						SLOT(executeInstructions()));
	connect(refresh, SIGNAL(timeout()), this, SLOT(refreshUI()));
	refresh->start(80);
}

void InputManagerWidget::refreshUI()
{
	std::string threads = std::to_string(svm->getSlaves());

	_T().action([&](){
		int client;
		std::string msg;
		while ((client = server.connection())) {
			std::vector<std::string> values;
			msg = server.receiveMessage(client);
			msg = msg.substr(5, msg.size() - 1);
			msg >> values;
			for (auto a : values)
				std::cout << a << std::endl;
		}
	}).run();
	monitoring->setText(std::string("Running threads: ").data());
}

void InputManagerWidget::choosePath()
{
	path->setText(QFileDialog::getOpenFileName());
}

void InputManagerWidget::executeInstruction(const unsigned int infoIndex)
{
	std::string line;
	std::vector<std::string> labels = {"EMAIL_ADDRESS",
					"PHONE_NUMBER",
					"IP_ADDRESS"};

	line = path->text().toStdString() + " " + labels[infoIndex];
	Command m(line);
	m.parseCommand();
	Information info(m);
	Scraper scraper(info);
	scraper.checkFiles();
	svm->createSlave(scraper, line);
}

void InputManagerWidget::executeInstructions()
{
	std::ifstream file(path->text().toStdString());
	std::vector<QRadioButton *> buttons = {checkBox1, checkBox2, checkBox3};

	if (!file.is_open()) {
		std::cerr << "Selected file couldnt be found or is empty."
			<< std::endl;
		return;
	}
	if (!checkBox1->isChecked() && !checkBox2->isChecked()
						&& !checkBox3->isChecked()) {
		std::cerr << "No parsing informations selected." << std::endl;
		return;
	}
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i]->isChecked()) {
			executeInstruction(i);
			history.push_back({path->text().toStdString(), i});
			break;
		}
	}
}

void InputManagerWidget::mousePressEvent(QMouseEvent *event)
{
	return QWidget::mousePressEvent(event);
}

void InputManagerWidget::mouseMoveEvent(QMouseEvent *event)
{
	return QWidget::mouseMoveEvent(event);
}