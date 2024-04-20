/**
 *	@file	Classes/NetworkHandler/TCPProtocolHandler/TCPProtocolHandler.cpp
 *	@brief	TCPProtocolHandler class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */
#include "TCPProtocolHandler.hpp"


/**
 * @brief Constructor for this class.
 *
 * This constructor initializes the `serverAddress_` and `serverDefaultPort` member variables.
 * 
 * @param serverAddress The IP address or hostname of the server to connect to.
 * @param serverDefaultPort The default port number to use for the server.
 */
TCPProtocolHandler::TCPProtocolHandler(const std::string& serverAddress, int serverDefaultPort) : serverAddress_(serverAddress), serverDefaultPort(serverDefaultPort) {

	if(!this->createSocket()) 
		throw NetworkException("Socket was not created.");
	if(!this->setUpServerAddressStructure()) 
		throw NetworkException("Server address was not created.");
	if(!this->bindSocketToTheAddress()) 
		throw NetworkException("Binding was wrong.");
	
}


/**
 * @brief Destructor for this class.
 *
 * This destructor is responsible for closing the socket (if open).
 */
TCPProtocolHandler::~TCPProtocolHandler() {

	if (this->socketDescriptor_ != -1) {
		close(this->socketDescriptor_);
	}

}


/**
 * @brief Destructor for this class.
 *
 * This destructor is responsible for closing the socket (if open).
 */
void TCPProtocolHandler::cleanupOnExit() {

    std::cout << "TCPProtocolHandler cleaning up..." << std::endl;
    if (this->socketDescriptor_ != -1) {
		close(this->socketDescriptor_);
	}

}


/**
 * @brief Creates a TCP socket.
 *
 * This function attempts to create a TCP socket using the `socket` system call.
 * On success, it stores the socket descriptor in the `this->socketDescriptor_` member variable.
 * 
 * @return true on successful socket creation, false otherwise.
 */
bool TCPProtocolHandler::createSocket() {

	this->socketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketDescriptor_ == -1) {
		std::cerr << ANSI_COLOR_RED << "Error creating socket: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
		return false;
	}

	return true;

}


/**
 * @brief Sets up the server address structure.
 *
 * This function fills a `struct sockaddr_in` structure with the provided server address 
 * and default port number. This structure is used later for binding the socket to the address.
 * 
 * @return true on successful address structure setup, false otherwise.
 */
bool TCPProtocolHandler::setUpServerAddressStructure() {

	memset(&this->serverAddr, 0, sizeof(this->serverAddr));
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_port = htons(this->serverDefaultPort);
	if (inet_pton(AF_INET, serverAddress_.c_str(), &this->serverAddr.sin_addr) <= 0) {
		std::cerr << ANSI_COLOR_RED << "Error converting server address: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
		close(this->socketDescriptor_);
		this->socketDescriptor_ = -1;
		return false;
	}

	return true;

}


/**
 * @brief Binds the socket to the specified server address.
 *
 * This function uses the `bind` system call to associate the socket (created by `createSocket`) 
 * with the server address and port number (defined in `serverAddress_` and `serverDefaultPort`).
 * 
 * @return true on successful binding, false otherwise.
 */
bool TCPProtocolHandler::bindSocketToTheAddress() {

	if (bind(this->socketDescriptor_, (struct sockaddr*)&this->serverAddr, sizeof(this->serverAddr)) < 0) {
		std::cerr << ANSI_COLOR_RED << "Error binding socket: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
		close(this->socketDescriptor_);
		this->socketDescriptor_ = -1;
		return false;
	}

	return true;

}


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
bool TCPProtocolHandler::listenForSockets(UserFactory *users, int breakPoint = -1) {

	// Listen for incoming connections
	if (listen(this->socketDescriptor_, 1) < 0) {
		std::cerr << ANSI_COLOR_RED << "Error listening for connections: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
		close(this->socketDescriptor_);
		this->socketDescriptor_ = -1;
		throw NetworkException("Network problem.");
		return false;
	}

	// Prepare poll structure
	struct pollfd pfd;
	pfd.fd = this->socketDescriptor_;
	pfd.events = POLLIN; // Interested in readability

	while (true) {
		// Wait for incoming data with poll
		int pollResult = poll(&pfd, 1, -1); // Wait indefinitely
		if (pollResult == -1) {
			std::cerr << ANSI_COLOR_RED << "Error in poll: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
			throw NetworkException("Network problem.");

			break;
		}
		else if (pollResult == 0) {
			// Timeout (unlikely with -1 in timeout)
			continue;
		}

		// Check for readable socket
		if (pfd.revents & POLLIN) {
			// Accept connection (not strictly necessary here, but included for completeness)
			struct sockaddr_storage clientAddr;
			socklen_t clientAddrSize = sizeof(clientAddr);
			int clientSocket = accept(this->socketDescriptor_, (struct sockaddr*)&clientAddr, &clientAddrSize);
			if (clientSocket == -1) {
				std::cerr << ANSI_COLOR_RED << "Error accepting connection: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
				throw NetworkException("Network problem.");
				continue;
			}

			// Receive data from the client
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));
			ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (bytesReceived == -1) {
				std::cerr << ANSI_COLOR_RED << "Error receiving data: " << strerror(errno) << ANSI_COLOR_RESET << std::endl;
				close(clientSocket);
				throw NetworkException("Network problem.");
				continue;
			} else if (bytesReceived == 0) {
				close(clientSocket);
				continue;
			}


			/**
			 * PROCESS RECEIVED DATA
			 */ 
			std::string receivedData(buffer, bytesReceived);
  			receivedData.erase(std::remove(receivedData.begin(), receivedData.end(), '\n'), receivedData.end());
  			users->addNewUser("adam", "xlicxz", "secret");
			// todo... 1) send back packet, 2) save it to user, make just authorization first (use class Message and then class ClientRequestProcessor). Then add all other opperations
			// do not forget use FiniteStateMachine
			//std::cout << receivedData << std::endl;
			close(clientSocket);


			// For development and tests (to know on how much sockets wait)
			if(breakPoint != -1) {
				if(breakPoint == 1) {
					return true;
				}
				else {
					breakPoint = breakPoint - 1;
				}
			}
		}
	}

	// Close the listening socket (important on program termination)
	close(this->socketDescriptor_);
	return true;

}
