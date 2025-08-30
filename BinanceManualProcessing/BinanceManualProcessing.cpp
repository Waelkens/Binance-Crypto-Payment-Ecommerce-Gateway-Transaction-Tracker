// BinanceManualProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#pragma comment(lib, "wininet.lib")

#define HTTP_USER_AGENT "HTTPRIP"
#define BUFFER_SIZE 512

using namespace std;

std::string replace_all(std::string subject, const std::string& search, const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}


inline std::string download_url(const std::string& url) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	std::string rtn;

	if (interwebs) {
		HINTERNET url_file = InternetOpenUrlA(interwebs, url.c_str(), NULL, NULL, NULL, NULL);

		if (url_file) {
			char buffer[2000];
			DWORD bytes_read;

			do {
				InternetReadFile(url_file, buffer, 2000, &bytes_read);
				rtn.append(buffer, bytes_read);
				memset(buffer, 0, 2000);
			} while (bytes_read);

			InternetCloseHandle(interwebs);
			InternetCloseHandle(url_file);
			std::string p = replace_all(rtn, "|n", "\r\n");
			return p;
		}
	}

	InternetCloseHandle(interwebs);
	std::string p = replace_all(rtn, "|n", "\r\n");
	return p;
}

int main()
{
	std::vector<std::string> keys{};

	std::string lastorderid;
	std::cout << "Running on 54.64.239.183:3306 (BINANCE.COM) " << std::endl;
	while (true) {
		Sleep(5000);
		std::string content = download_url("https://api.fuzion-fq.ru/lastorderid.txt");
		if (content != lastorderid) {
			lastorderid = content;
			keys.push_back(content);
			Sleep(3000);
			for (int i = 0; i < lastorderid.size(); i++) {
				std::string command = "start chrome https://www.binance.com/nl/my/wallet/exchange/deposit/fiat/order/result/CKO-IDEAL/" + keys[i] + "?cko-session-id=sid_ovnoanjrdovujh5nkom4hoktee";
				system(command.c_str());
			}

			
		}

	



	}
	 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
