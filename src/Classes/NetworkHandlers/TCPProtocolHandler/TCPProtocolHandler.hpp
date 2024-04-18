
/**
 *	@file	test/NetworkHandler/TCPProtocolHandler/TCPProtocolHandler.cpp
 *	@brief	TCPProtocolHandler class header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef TCPPROTOCOLHANDLER_HPP
#define TCPPROTOCOLHANDLER_HPP

// Libraries
#include <iostream>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <array>

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class TCPProtocolHandler
 *  This class operate with TCP protocol
 */
class TCPProtocolHandler {
private:
    std::string server;
    uint16_t port;

public:

    int clientSocket;
	struct hostent* host;
	struct sockaddr_in serverAddress;

    TCPProtocolHandler(const std::string& server, int port);

	bool connect();
	bool disconnect();


	// Communication functions
    void send(const std::string& message);
    std::string receive();

    std::string getServer() const;
    uint16_t getPort() const;

};

#endif // TCPPROTOCOLHANDLER_HPP