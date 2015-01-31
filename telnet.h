#ifndef TELNET_H
#define TELNET_H

#include <string>

#include "libtelnet.h"

class TelnetDelegate
{
	public:
		virtual void didReceiveData(const char *buffer, size_t size) = 0;
};

class Telnet
{
	public:
		Telnet(const char *hostname, const char *service);
		~Telnet();

		bool connect();
		void disconnect();
		void send(const char *buffer, size_t size);

		TelnetDelegate *delegate;

	private:
		std::string service_;
		std::string hostname_;

		int sockfd;
		telnet_t* telnet;
};

#endif // TELNET_H
