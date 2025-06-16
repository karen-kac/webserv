#include "../inc/webserv.hpp"
#include "../inc/Server.hpp"

int main (int argc, char* argv[])
{
	std::string configPath = DEFAULT_CONFIG;

	// コマンドライン引数チェック
	if (argc > 1)
	{
		std::string arg = argv[1];
		if (arg == "--help" || arg == "-h")
		{
			printUsage(argv[0]);
			return 0;
		}
		else if()
		{

		}

	}
}