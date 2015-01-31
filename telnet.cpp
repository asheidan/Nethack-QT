#include "telnet.h"

#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <iostream>

Telnet::Telnet(const char *hostname, const char *service)
	: delegate(NULL), service_(service), hostname_(hostname),
	  sockfd(-1), telnet(NULL)
{}

Telnet::~Telnet()
{
	if (-1 != this->sockfd) {
		close(this->sockfd);
		this->sockfd = -1;
	}

	if (NULL != this->telnet) {
		telnet_free(this->telnet);
		this->telnet = NULL;
	}
}

bool Telnet::connect()
{
	int
			error;
	struct addrinfo
			hints;
	struct addrinfo
			*address, *cur_address;
	char ip[INET6_ADDRSTRLEN];
	int port;

	memset(ip, 0, sizeof(char)*INET6_ADDRSTRLEN);

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	error = getaddrinfo(this->hostname_.c_str(), this->service_.c_str(),
						&hints, &address);
	if (0 != error || NULL == address) {
		std::cerr << "getaddrinfo(): " << gai_strerror(error) << std::endl;
	}

	for (cur_address = address; cur_address; cur_address = cur_address->ai_next) {
		if (AF_INET == address->ai_family) {
			struct sockaddr_in *data;
			data = (struct sockaddr_in *)address->ai_addr;

			const char *result = inet_ntop(address->ai_family, &data->sin_addr,
									 ip, INET6_ADDRSTRLEN);
			if (NULL == result) {
				std::cout << "inet_ntop(): " << strerror(errno) << std::endl;
			}
			port = ntohs(data->sin_port);
		}

		this->sockfd = ::socket(address->ai_family, address->ai_socktype,
							  address->ai_protocol);
		if (0 > this->sockfd) {
			std::cerr << "connect(): " << strerror(errno) << std::endl;
			continue;
		}

		error = ::connect(this->sockfd, address->ai_addr, address->ai_addrlen);
		if (0 != error) {
			std::cerr << "connect(): " << strerror(errno) << std::endl;
			close(this->sockfd);
			this->sockfd = -1;
			continue;
		}
		std::cerr << "Connected!" << std::endl;
		break;
	}

	freeaddrinfo(address);

	return !(0 > this->sockfd);
}

void Telnet::disconnect()
{
	::close(this->sockfd);
	this->sockfd = -1;
}
