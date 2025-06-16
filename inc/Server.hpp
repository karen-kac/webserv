#ifndef SERVER_HPP
#define SERVER_HPP

#include "webserv.hpp"

class Server {
private:
	bool _running;

public:
	Server();
	Server(const std::string& configPath);
	~Server();
	// Server& operator=(const Server& other);

	bool initialize();
	void run();
	void stop();


};

#endif