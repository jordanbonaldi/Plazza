/*
** EPITECH PROJECT, 2018
** SocketClient
** File description:
** Implementation of SocketClient
*/

#include <cstring>
#include <iostream>
#include "SocketClient.hpp"

SocketClient::SocketClient(const std::string &ipAdress, int port) :
						ipAdress(ipAdress.c_str()),
						port(port)
{

}

int SocketClient::create()
{
	struct protoent *pe;
	int enable = 1;

	if (!(pe = getprotobyname("TCP")))
	{
		return (fprintf(stderr, "getprotobyname error\n"));
	}
	if ((fd = socket(AF_INET, SOCK_STREAM,
			  pe->p_proto)) < 0)
	{
		perror("socket");
		return 1;
	}
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	{
		perror("setsockopt");
		return 1;
	}
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ipAdress);
	return (0);
}

int SocketClient::connection()
{
	if (connect(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
		perror("connect");
		return 1;
	}
	return (0);
}

int SocketClient::disconnection()
{
	if (close(fd) == -1)
		return (84);
	return 0;
}

int SocketClient::sendMessage(const std::string &string)
{
	if (send(fd, string.c_str(), string.size(), 0) == -1)
	{
		perror("write");
		return 1;
	}
	return 0;
}

std::string SocketClient::receiveMessage()
{
	std::string msg = "";
	char a;

	while (recv(fd, &a, 1, 0) > 0)
	{
		if (a == '\n' || !a)
			break;
		msg.push_back(a);
	}
	return msg;
}
