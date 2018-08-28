##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

RM = rm -f

CXXFLAGS += -Iinclude/ -IGUI/include
CXXFLAGS += -W -Wextra -Wall -Werror -std=c++17 -g3 -fpic

GUIFLAGS = -lQt5Core -lQt5Widgets -lQt5Charts -DQT_NO_VERSION_TAGGING

NAME = plazza

GUINAME = graphical_plazza

SRCS =  src/main.cpp \
		src/Input.cpp \
		src/Command.cpp \
		src/InputManager.cpp \
		src/Scraper.cpp \
		src/Information.cpp \
		src/SocketClient.cpp \
		src/SocketServer.cpp \

GUISRCS =	GUI/src/main.cpp \
		GUI/src/MainWindow.cpp		\
		GUI/src/InputManagerWidget.cpp	\
		src/Input.cpp \
		src/Command.cpp \
		src/InputManager.cpp \
		src/Scraper.cpp \
		src/Information.cpp \
		src/SocketClient.cpp \
		src/SocketServer.cpp \

OBJS = $(SRCS:.cpp=.o)

GUIOBJS = $(GUISRCS:.cpp=.o)

all: $(NAME)

moc:
	moc GUI/include/InputManagerWidget.hpp -o GUI/include/InputManagerWidget.moc

ui: moc $(GUINAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lpthread

$(GUINAME): $(GUIOBJS)
	$(CC) $(GUIOBJS) -o $(GUINAME) -lpthread $(GUIFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(GUIOBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(GUINAME)

re: fclean all

.PHONY: all ui clean fclean re
