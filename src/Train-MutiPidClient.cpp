//============================================================================
// Name        : Train-MutiPidClient.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

#define PORT 1234
#define MAXDATASIZE 1000

int main(int argc, char *argv[]) {
	int fd, num;
	char buf[MAXDATASIZE];
	char rvbuf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in server;
	int i = 1;
	if (argc != 2) {
		printf("ip%s\n", argv[1]);
		exit(-1);
	}

	if ((he = gethostbyname(argv[1])) == NULL) {
		printf("gethostbyname() error");
		exit(1);
	}

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error.");
		exit(1);
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
//	server.sin_addr = *((struct in_addr *) he->h_addr);
	memcpy(&server.sin_addr, he->h_addr,sizeof(struct in_addr));
	if (connect(fd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("connect() error.");
		exit(1);
	}

	if ((num = recv(fd, buf, MAXDATASIZE, 0)) == -1) {
		perror("recv() error.");
		exit(1);
	}
	buf[num] = '\0';
	printf("Server MSG:%slen:%d\n", buf, num);
	printf("Input name:");
	scanf("%s", buf);
	if ((num = send(fd, buf, strlen(buf), 0)) == -1) {
		perror("send() error.");
		exit(1);
	}
	while (i) {
		printf("INPUT MSG max Num:%d:",MAXDATASIZE);
		scanf("%s", buf);
		if (strlen(buf) < 1)
			i = 0;
		if ((num = send(fd, buf, strlen(buf), 0)) == -1) {
			perror("send() error.");
			exit(1);
		}

		if ((num = recv(fd, buf, MAXDATASIZE, 0)) == -1) {
			perror("read() error.");
			exit(1);
		}
		buf[num] = '\0';
		printf("%s\n", buf);

	}

	close(fd);

}

