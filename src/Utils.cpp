#include "../inc/webserv.hpp"

namespace Utils {

// 先頭・末尾の空白・改行・タブを除去
std::string trim(const std::string& str) {
	// 先頭の空白・改行・タブ以外の文字が見つかる位置
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos)
		return "";
	// 末尾の空白・改行・タブ以外の文字が見つかる位置
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}

// 小文字に変換
std::string toLower(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}

// 大文字に変換
std::string toUpper(const std::string& str) {
	std::string result = str;
	std::transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

// 文字列を指定された区切り文字で分割
std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
	std::vector<std::string> tokens;
	if (str.empty() || delimiter.empty())
		return tokens;

	size_t start = 0;
	size_t pos = 0;
	// std::string::nposは、findメソッドが見つからない場合の戻り値
	// intに入れると-1になる
	while ((pos = str.find(delimiter, start)) != std::string::npos) {
		if (pos > start) {
			tokens.push_back(str.substr(start, pos - start));
		}
		start = pos + delimiter.length();
	}
	// 最後の区切り文字の後ろの文字列があれば追加
	if (start < str.length()) {
		tokens.push_back(str.substr(start));
	}
	return tokens;
}

// 現在の時刻を取得
std::string getCurrentTime() {
	// UNIX時刻の秒数を取得
	time_t now = time(0);
	// UTC（GMT）として変換→HTTPレスポンスの日付と時刻を指定するため
	struct tm* timeinfo = gmtime(&now);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", timeinfo);
	return std::string(buffer);
}

// ファイルの拡張子に応じたMIMEタイプを取得
std::string getMimeType(const std::string& extension) {
	std::string ext = toLower(extension);
	
	if (ext == ".html" || ext == ".htm")
		return "text/html";
	else if (ext == ".css")
		return "text/css";
	else if (ext == ".js")
		return "application/javascript";
	else if (ext == ".json")
		return "application/json";
	else if (ext == ".xml")
		return "application/xml";
	else if (ext == ".txt")
		return "text/plain";
	else if (ext == ".jpg" || ext == ".jpeg")
		return "image/jpeg";
	else if (ext == ".png")
		return "image/png";
	else if (ext == ".gif")
		return "image/gif";
	else if (ext == ".ico")
		return "image/x-icon";
	else if (ext == ".pdf")
		return "application/pdf";
	else if (ext == ".zip")
		return "application/zip";
	else if (ext == ".tar")
		return "application/x-tar";
	else if (ext == ".gz")
		return "application/gzip";
	else
		// 未知の拡張子の場合は、application/octet-streamとして扱う（バイナリデータ）
		return "application/octet-stream";
}

// ステータスコードに応じたメッセージを取得
std::string getStatusMessage(int code) {
	switch (code) {
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 301: return "Moved Permanently";
		case 302: return "Found";
		case 400: return "Bad Request";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 408: return "Request Timeout";
		case 411: return "Length Required";
		case 413: return "Payload Too Large";
		case 414: return "URI Too Long";
		case 500: return "Internal Server Error";
		case 501: return "Not Implemented";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 505: return "HTTP Version Not Supported";
		default: return "Unknown";
	}
}

// ファイルが存在するかどうかを確認
bool fileExists(const std::string& path) {
	struct stat buffer;
	// ファイル情報を取得
	return (stat(path.c_str(), &buffer) == 0);
}

// ディレクトリかどうかを確認
bool isDirectory(const std::string& path) {
	struct stat buffer;
	if (stat(path.c_str(), &buffer) != 0)
		return false;
	// ファイルがディレクトリかどうかを確認（マクロ）
	return S_ISDIR(buffer.st_mode);
}

// ファイルを読み込む
std::string readFile(const std::string& path) {
	// ファイルをバイナリモードで読み込む
	std::ifstream file(path.c_str(), std::ios::binary);
	if (!file.is_open())
		return "";
	
	std::ostringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

// 16進数を10進数に変換
size_t hexToDecimal(const std::string& hex) {
	size_t result = 0;
	for (size_t i = 0; i < hex.length(); ++i) {
		char c = hex[i];
		if (c >= '0' && c <= '9')
			result = result * 16 + (c - '0');
		else if (c >= 'a' && c <= 'f')
			result = result * 16 + (c - 'a' + 10);
		else if (c >= 'A' && c <= 'F')
			result = result * 16 + (c - 'A' + 10);
		else
			break;
	}
	return result;
}

// URLエンコードされた文字列をデコードする
// スペースは+または%20に変換
// パーセントエンコードされた文字は16進数に変換（%2Fは/）
std::string urlDecode(const std::string& str) {
	std::string result;
	for (size_t i = 0; i < str.length(); ++i) {
		if (str[i] == '%' && i + 2 < str.length()) {
			// ％から始まる2文字の16進数を取得
			std::string hex = str.substr(i + 1, 2);
			if (hex.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos) {
				char c = static_cast<char>(hexToDecimal(hex));
				result += c;
				i += 2;
			} else {
				result += str[i];
			}
		} else if (str[i] == '+') {
			result += ' ';
		} else {
			result += str[i];
		}
	}
	return result;
}

// ディレクトリリスティングを生成（指定されたURIのディレクトリの内容をHTMLで表示）
std::string generateDirectoryListing(const std::string& path, const std::string& uri) {
	// ディレクトリリスティングのHTMLを生成
	std::string html;
	html += "<!DOCTYPE html>\n";
	html += "<html>\n<head>\n";
	html += "<title>Index of " + uri + "</title>\n";
	html += "<style>\n";
	html += "body { font-family: Arial, sans-serif; margin: 20px; }\n";
	html += "h1 { color: #333; }\n";
	html += "table { border-collapse: collapse; width: 100%; }\n";
	html += "th, td { text-align: left; padding: 8px; border-bottom: 1px solid #ddd; }\n";
	html += "th { background-color: #f2f2f2; }\n";
	html += "a { text-decoration: none; color: #0066cc; }\n";
	html += "a:hover { text-decoration: underline; }\n";
	html += "</style>\n";
	html += "</head>\n<body>\n";
	html += "<h1>Index of " + uri + "</h1>\n";
	html += "<table>\n";
	html += "<tr><th>Name</th><th>Size</th><th>Last Modified</th></tr>\n";
	
	// 新規ディレクトリの場合は、親ディレクトリのURIを取得
	if (uri != "/") {
		std::string parentUri = uri;
		if (parentUri.length() > 1 && parentUri[parentUri.length() - 1] == '/')
			parentUri = parentUri.substr(0, parentUri.length() - 1);
		size_t lastSlash = parentUri.find_last_of('/');
		if (lastSlash != std::string::npos)
			parentUri = parentUri.substr(0, lastSlash + 1);
		html += "<tr><td><a href=\"" + parentUri + "\">[Parent Directory]</a></td><td>-</td><td>-</td></tr>\n";
	}
	
	// ディレクトリの内容を読み込む
	DIR* dir = opendir(path.c_str());
	if (dir) {
		struct dirent* entry;
		while ((entry = readdir(dir)) != NULL) {
			// ドットから始まるファイルは無視
			if (entry->d_name[0] == '.')
				continue;
			std::string fullPath = path + "/" + entry->d_name;
			std::string linkUri = uri;
			if (linkUri[linkUri.length() - 1] != '/')
				linkUri += "/";
			linkUri += entry->d_name;
			// ファイル情報を取得
			struct stat fileStat;
			if (stat(fullPath.c_str(), &fileStat) == 0) {
				std::string name = entry->d_name;
				if (S_ISDIR(fileStat.st_mode)) {
					name = "[" + name + "]";
					linkUri += "/";
				}
				// ファイルの更新日時を取得
				char timeStr[80];
				struct tm* timeinfo = localtime(&fileStat.st_mtime);
				strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M", timeinfo);
				
				std::ostringstream sizeStr;
				if (S_ISDIR(fileStat.st_mode))
					sizeStr << "-";
				else
					sizeStr << fileStat.st_size;

				// ディレクトリリスティングのHTMLを生成
				html += "<tr><td><a href=\"" + linkUri + "\">" + name + "</a></td>";
				html += "<td>" + sizeStr.str() + "</td>";
				html += "<td>" + std::string(timeStr) + "</td></tr>\n";
			}
		}
		closedir(dir);
	}
	
	html += "</table>\n</body>\n</html>\n";
	return html;
}

}