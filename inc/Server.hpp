#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"
#include "Config.hpp"

class Server {
private:
	Config* _config;
	std::vector<int> _serverSockets;
	bool _running;

	void signalHandler(int sig);

public:
	Server();
	Server(const std::string& configPath);
	~Server();
	// Server& operator=(const Server& other);

	bool initialize();
	void run();
	void stop();

	// Static signal handler wrapper
	static Server* instance;
	static void staticSiganlHandler(int sig);
};

#endif