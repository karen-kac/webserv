# include "../inc/Server.hpp"

Server::Server() : _config(NULL), _running(false){
	instance = this;
}