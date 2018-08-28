/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

# include <Input.hpp>
# include <InputManager.hpp>

int main(const int argc, char const * const * argv)
{
	SocketServer server;

	if (argc < 2)
		return 84;
	server.create();
	InputManager im(atoi(argv[1]), server.getPort());
	im.build();
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
	}).run().join();
	while (true) {

		if (im.getSlaveManager().isDone())
			break;
		sleep(1);
	}
	return 0;
}
