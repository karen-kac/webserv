#include "../inc/webserv.hpp"
#include "../inc/Server.hpp"

void printUsage(const std::string& programName)
{
	std::cout << "Usage: " << programName << " [configuration_file]" << std::endl;
	std::cout << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "  configuration_file    Path to the configuration file (optional)" << std::endl;
	std::cout << "                       Default: " << DEFAULT_CONFIG << std::endl;
	std::cout << "  --help, -h           Show this help message" << std::endl;
	std::cout << "  --version, -v        Show version information" << std::endl;
	std::cout << std::endl;
	std::cout << "Examples:" << std::endl;
	std::cout << "  " << programName << "                    # Use default configuration" << std::endl;
	std::cout << "  " << programName << " my_config.conf     # Use custom configuration" << std::endl;
}
void printVersion()
{
	std::cout << "Webserv 1.0" << std::endl;
	std::cout << "HTTP/1.1 compliant web server implementation" << std::endl;
	std::cout << "Built with C++98 standard" << std::endl;
}

void printWelcome()
{
	std::cout << "Welcome to Webserv" << std::endl;
}
int main (int argc, char* argv[])
{
	std::string configPath = DEFAULT_CONFIG;

	// コマンドライン引数チェック
	if (argc > 1)
	{
		std::string arg = argv[1];
		if (arg == "--help" || arg == "-h")
		{
			// ヘルプメッセージの表示
			printUsage(argv[0]);
			return 0;
		}
		else if(arg == "--version" || arg == "-v")
		{
			printVersion();
			return 0;
		}
		else
			configPath = arg;
	}

	if (argc > 2)
	{
		std::cerr << "Error:Too many arguments" << std::endl;
		printUsage(argv[0]);
		return 1;
	}
}