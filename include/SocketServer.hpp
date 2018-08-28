/*
** EPITECH PROJECT, 2018
** SocketServer
** File description:
** Declaration of SocketServer
*/

#ifndef NANOTEKSPICE_SOCKETSERVER_HPP
	#define NANOTEKSPICE_SOCKETSERVER_HPP

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <libgen.h>
#include <string>

class SocketServer
{
public:
	SocketServer(int port = 0);
	int create();
	int connection();
	int disconnection();
	int sendMessage(const std::string &string, int);
	std::string receiveMessage(int);
	int getPort() const;
private:
	int fd;
	int clientFd;
	int port;
	struct sockaddr_in s_in_client;
	struct sockaddr_in s_in;
};


#endif //NANOTEKSPICE_SOCKETSERVER_HPP
