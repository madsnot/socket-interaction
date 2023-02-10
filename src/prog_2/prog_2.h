#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <cstring>
#include <iostream>

using namespace std;

class Reviewer {
	int dataLength;
    int sockfd;
    struct sockaddr_in servaddr;

public:
    void initSocket() {
        if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
            perror("socket creation failed");
            exit(EXIT_FAILURE);
        }

        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family    = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(3000);

        if ( bind(sockfd, (const struct sockaddr *)&servaddr,
                  sizeof(servaddr)) < 0 )
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
    }

	void RunReviewer() {
        recv(sockfd, &dataLength, sizeof(int),
                 MSG_WAITALL);
		if (dataLength / 100 > 0 && dataLength % 32 == 0)
			cout << "prog_2: Data received" << endl;
		else
			cout << "prog_2: Error data" << endl;
	}
};
