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
void Server::signalHandler(int sig) {
	switch (sig) {
		case SIGINT: // Ctrl+C
		case SIGTERM: // kill command
			std::cout << std::endl << "Received signal " << sig << ", shutting down..." << std::endl;
			_running = false;
			break;
	}
}

void Server::staticSiganlHandler(int sig) {
	if (instance) {
		instance->signalHandler(sig);
	}
}

bool Server::initialize() {
	// シグナルハンドラ設定
	signal(SIGINT, staticSiganlHandler);
	signal(SIGTERM, staticSiganlHandler);
	signal(SIGPIPE, SIG_IGN);
	
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