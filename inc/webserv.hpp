#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <csignal>
#include <ctime>
#include <climits>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <poll.h>

#define BUFFER_SIZE 8192
#define MAX_CONNECTIONS 1000
#define TIMEOUT 60
#define DEFAULT_CONFIG "default.conf"

// ステータスコード
#define HTTP_OK 200
#define HTTP_CREATED 201
#define HTTP_NO_CONTENT 204
#define HTTP_MOVED_PERMANENTLY 301
#define HTTP_FOUND 302
#define HTTP_BAD_REQUEST 400
#define HTTP_FORBIDDEN 403
#define HTTP_NOT_FOUND 404
#define HTTP_METHOD_NOT_ALLOWED 405
#define HTTP_REQUEST_TIMEOUT 408
#define HTTP_LENGTH_REQUIRED 411
#define HTTP_PAYLOAD_TOO_LARGE 413
#define HTTP_URI_TOO_LONG 414
#define HTTP_INTERNAL_SERVER_ERROR 500
#define HTTP_NOT_IMPLEMENTED 501
#define HTTP_BAD_GATEWAY 502
#define HTTP_SERVICE_UNAVAILABLE 503
#define HTTP_HTTP_VERSION_NOT_SUPPORTED 505

class Server;
class Config;
class Request;
class Response;
class Location;
class CGI;
class HttpParser;

// 名前の衝突を避け、関連する関数をまとめて管理する
namespace Utils {
	std::string trim(const std::string& str);
	std::string toLower(const std::string& str);
	std::string toUpper(const std::string& str);
	std::vector<std::string> split(const std::string& str, const std::string& delimiter);
	std::string getCurrentTime();
	std::string getMimeType(const std::string& extension);
	std::string getStatusMessage(int code);
	bool fileExists(const std::string& path);
	bool isDirectory(const std::string& path);
	std::string readFile(const std::string& path);
	size_t hexToDecimal(const std::string& hex);
	std::string urlDecode(const std::string& str);
	std::string generateDirectoryListing(const std::string& path, const std::string& uri);
}

#endif
