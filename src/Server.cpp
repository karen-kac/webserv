# include "../inc/Server.hpp"
# include "../inc/CGI.hpp"

// Static member initialization
Server* Server::instance = NULL;

Server::Server() : _config(NULL), _running(false) {
	instance = this;
}

Server::Server(const std::string& configPath) : _config(NULL), _running(false) {
	instance = this;
}

Server::~Server() {
	stop();
	delete _config;
	instance = NULL;
}

bool Server::initialize() {

	return true;
}

void Server::run() {
	_running = true;
	while (_running) {

	}
}

void Server::stop() {
	_running = false;
}