#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<char> buf;

class Parser {
public:
	bool validStr(string str) {
		if (str.length() > 64)
			return false;
		for (char symb : str) {
			if ((int)symb - 48 > 9)
				return false;
		}
		return true;
	}
	void changeEvenNumToKB(string str) {
		for (char symb : str) {
			if (((int)symb - 48) % 2 == 0) {
				buf.push('K');
				buf.push('B');
			}
			else
				buf.push(symb);
		}
	}

};

class DataHandler : public Parser {
	enum class Status { idle, ready };
	Status progress = Status::idle;
	mutex data;
	condition_variable bell;
    int sockfd;
    char sockBuf[4];
    struct sockaddr_in servaddr;

    void initSocket() {
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(3000);
        servaddr.sin_addr.s_addr = INADDR_ANY;
    }

public:
	static bool comp(char a, char b) {
		return a > b;
	}
	void RunParser() {
		unique_lock<mutex> lg(data);
		cout << "prog_1. Parser work: " << endl;
		string str;
		cin >> str;
		if (validStr(str)) {
			sort(str.begin(), str.end(), DataHandler::comp);
			changeEvenNumToKB(str);
		}
		progress = Status::ready;
		bell.notify_one();
	}
	void RunHandler() {
		unique_lock<mutex> ul(data);
		bell.wait(ul, [=]() { return progress == Status::ready; });
		cout << "prog_1. Handler work: " << endl;
		string str = "";
		char symb;
		int sum = 0, num;
		while (!buf.empty()) {
			symb = buf.front();
			cout << symb;
			num = (int)symb - 48;
			if (num <= 9)
				sum += num;
			buf.pop();
		}
        cout << endl;
		progress = Status::idle;
        initSocket();
        sendto(sockfd, &sum, sizeof(int),
               MSG_CONFIRM, (const struct sockaddr *) &servaddr,
               sizeof(servaddr));
	}
};
