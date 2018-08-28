/*
** EPITECH PROJECT, 2018
** SocketServer
** File description:
** Implementation of SocketServer
*/

#include <cstring>
#include <iostream>
#include "SocketServer.hpp"

SocketServer::SocketServer(int port)
{
	this->port = port;
}

int SocketServer::create()
{
	struct protoent *pe;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(this->port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	if (!(pe = getprotobyname("TCP")))
		return (1);
	if ((fd = socket(AF_INET, SOCK_STREAM,
			 pe->p_proto)) < 0)
		return (1);
	if (bind(fd, (const struct sockaddr *)&s_in,
		 sizeof(s_in)) == -1) {
		perror("bind");
		if (close(fd) == -1)
			return 1;
		return 1;
	}
	if (listen(fd, 42) == -1)
	{
		perror("listen");
		return 1;
	}
	return (0);
}

int SocketServer::connection()
{
	size_t size = sizeof(s_in_client);
	fd_set rfds;
	struct timeval tv;

	FD_ZERO(&rfds);
	FD_SET(fd, &rfds);
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	if (select(FD_SETSIZE, &rfds, NULL, NULL, &tv) <= 0)
		return (0);
	clientFd = accept(fd,
			(struct sockaddr *)&s_in_client,
			(socklen_t *)(&size));
	if (clientFd == -1)
	{
		perror("accept");
		return (0);
	}
	return (clientFd);
}

int SocketServer::disconnection()
{
	if (close(fd) == -1)
		return (84);
	if (close(clientFd) == -1)
		return (84);
	return 0;
}

int SocketServer::sendMessage(const std::string &string, int fdclient)
{
	if (send(fdclient, string.c_str(), string.size(), 0) == -1)
		perror("write");
	return 0;
}

std::string SocketServer::receiveMessage(int fdclient)
{
	std::string msg = "";
	char a;

	while (recv(fdclient, &a, 1, 0) > 0)
	{
		if (!a || a == '\n')
			break;
		msg.push_back(a);
	}
	return msg;
}
int SocketServer::getPort() const
{
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);

	if (getsockname(fd, (struct sockaddr *)&sin, &len) == -1)
	{
		perror("getsockname");
		return -1;
	}
	else
		return ntohs(sin.sin_port);
}
