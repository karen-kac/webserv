#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "webserv.hpp"

class Config {
private:
	std::string _configPath;

	bool parseConfigFile();

public:
	Config();
	Config(const std::string& configPath);
	~Config();

	// バリデーション
	bool isValid() const;
	void printConfig() const;
};

#endif