
/**
 *	@file	test/NetworkHandler/TCPProtocolHandler/TCPProtocolHandler.cpp
 *	@brief	TCPProtocolHandler class header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef TCPPROTOCOLHANDLER_HPP
#define TCPPROTOCOLHANDLER_HPP

// Libraries
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>
#include <map>
#include "../../ClientRequestProcessor/ClientRequestProcessor.hpp"
#include "../../UserFactory/UserFactory.hpp"

// Exceptions
#include "../../../Exceptions/NetworkException.cpp"

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

	/**
	 * @brief The server address.
	 *
	 * This variable stores the IP address of this server.
	 */
	std::string serverAddress_;

	/**
	 * @brief The file descriptor for the socket.
	 *
	 * This variable stores the file descriptor for the socket created by this object. 
	 * A value of -1 indicates that no socket is currently open.
	 */
	int socketDescriptor_ = -1;

	/**
	 * @brief The default port number for the server.
	 *
	 * This member variable stores the default port number that this object 
	 * will use when binding a socket. Default port number is in Classes/Arguuments/Arguments.cpp.
	 */
	int serverDefaultPort;

	/**
	* @brief The server address structure.
	*
	* This member variable stores a `struct sockaddr_in` that represents the server's address information. 
	* This structure is used later for binding the socket to the server's IP address and port number.
	*/
	struct sockaddr_in serverAddr;


public:

	/**
	 * @brief Constructor for this class.
	 *
	 * This constructor initializes the `serverAddress_` and `serverDefaultPort` member variables.
	 * 
	 * @param serverAddress The IP address or hostname of the server to connect to.
	 * @param serverDefaultPort The default port number to use for the server.
	 */
	TCPProtocolHandler(const std::string& serverAddress, int serverDefaultPort);

	/**
	 * @brief Destructor for this class.
	 *
	 * This destructor is responsible for closing the socket (if open).
	 */
	~TCPProtocolHandler();

	/**
	* @brief Destructor for this class.
	*
	* This destructor is responsible for closing the socket (if open).
	*/
	void cleanupOnExit();

	/**
	 * @brief Creates a TCP socket.
	 *
	 * This function attempts to create a TCP socket using the `socket` system call.
	 * On success, it stores the socket descriptor in the `socketDescriptor_` member variable.
	 * 
	 * @return true on successful socket creation, false otherwise.
	 */
	bool createSocket();

	/**
	 * @brief Sets up the server address structure.
	 *
	 * This function fills a `struct sockaddr_in` structure with the provided server address 
	 * and default port number. This structure is used later for binding the socket to the address.
	 * 
	 * @return true on successful address structure setup, false otherwise.
	 */
	bool setUpServerAddressStructure();

	/**
	 * @brief Binds the socket to the specified server address.
	 *
	 * This function uses the `bind` system call to associate the socket (created by `createSocket`) 
	 * with the server address and port number (defined in `serverAddress_` and `serverDefaultPort`).
	 * 
	 * @return true on successful binding, false otherwise.
	 */
	bool bindSocketToTheAddress();

	/**
	*	@brief Listens for and handles incoming TCP connections.
	*
	*	- Sets up listening socket.
	*	- Loops indefinitely:
	*		- Uses poll to monitor listening socket for connections.
	*		- On readable socket (incoming connection):
	*			 - Accepts connection and creates a new client socket.
	*			 - Processes client connection (replace comment).
	*		- Handles errors during listening or client connection.
	*	- Closes listening socket on exit.
	*
	*	@param users pointer on users to operate with it.
	*	@param breakPoint number of packet to receive. If it is -1, receive all infinitely.
	*	@return true on successful setup, false otherwise.
	*/
	bool listenForSockets(UserFactory *users, UserChannelRelationshipFactory *relationship, ChannelFactory *channels, int breakPoint);

};

#endif // TCPPROTOCOLHANDLER_HPP