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
bool TCPProtocolHandler::listenForSockets(UserFactory *users, UserChannelRelationshipFactory *relationship, ChannelFactory *channels, int breakPoint = -1) {

	// Listen for incoming connections
	if (listen(socketDescriptor_, 1) < 0) {
	  std::cerr << "Error listening for connections: " << strerror(errno) << std::endl;
	  close(socketDescriptor_);
	  socketDescriptor_ = -1;
	  throw NetworkException("Network problem.");
	  return false;
	}

	// Prepare poll structure (assuming all existing connections are added initially)
	std::vector<pollfd> fds;
	pollfd listen_fd;
	listen_fd.fd = socketDescriptor_;
	listen_fd.events = POLLIN; // Interested in readability
	fds.push_back(listen_fd);

	std::map<int, int> connectedClients; // Map client ID to socket descriptor
	int clientId = 0; // Generate unique client ID

	while (true) {
	  int pollResult = poll(fds.data(), fds.size(), -1);
	  if (pollResult == -1) {
		std::cerr << "Error in poll: " << strerror(errno) << std::endl;
		throw NetworkException("Network problem.");
		break;
	  } else if (pollResult == 0) {
		// Timeout (unlikely with -1 in timeout)
		continue;
	  }

	  // Check for events on existing connections and listening socket
	  for (size_t i = 0; i < fds.size(); ++i) {
		if (fds[i].revents & POLLIN) {
		  if (fds[i].fd == socketDescriptor_) {
			// New connection
			struct sockaddr_storage clientAddr;
			socklen_t clientAddrSize = sizeof(clientAddr);
			int clientSocket = accept(socketDescriptor_, (struct sockaddr*)&clientAddr, &clientAddrSize);
			if (clientSocket == -1) {
				std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
				throw NetworkException("Network problem.");
				continue;
			}
			// Add new client to map and poll structure
			connectedClients[++clientId] = clientSocket;
			fds.push_back({clientSocket, POLLIN, 0});
			} else {
			// Existing connection has data
			int clientSocket = fds[i].fd;
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));
			ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (bytesReceived == -1) {
				std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
				close(clientSocket);
				connectedClients.erase(clientSocket);
				fds.erase(fds.begin() + i); // Remove from poll structure
				continue;
			} else if (bytesReceived == 0) {
				close(clientSocket);
				connectedClients.erase(clientSocket);
				fds.erase(fds.begin() + i); // Remove from poll structure
				continue;
			}

			/**
			 * PROCESS RECEIVED DATA
			 */
			std::string receivedData(buffer, bytesReceived);
			receivedData.erase(std::remove(receivedData.begin(), receivedData.end(), '\n'), receivedData.end());

			// Get current client
			// Find the client ID for this socket
			int currentClientID = -1;
			for (const auto& client : connectedClients) {
				if (client.second == fds[i].fd) {
					currentClientID = client.first;
					break;
				}
			}
			if(currentClientID == -1)
				exit(658);
			
			// Parse message
			Message msg;
			msg.parseTCP(receivedData);

			if(msg.getMessageType() == Message::MessageType::JOIN && users->userExistsByUniqueID(currentClientID)) {
				users->findUserByUniqueID(currentClientID)->displayname = msg.getDisplayName();
			}

			// Process what user wants
			ClientRequestProcessor requestProcessor(&msg, users, currentClientID, relationship, channels);

			/**
			 *	RESPONSE
			 */
			std::string responseMessage;
			responseMessage += requestProcessor.getMessageTCP();
			responseMessage += "\r\n";

			// Send to current client
			if (msg.getMessageType() != Message::MessageType::MSG) {
				
				// Prepare and send response message
				if (msg.getMessageType() != Message::MessageType::MSG) {
					int bytesSent = send(clientSocket, responseMessage.c_str(), responseMessage.length(), 0);
					if (bytesSent == -1) {
					std::cerr << "Error sending data: " << strerror(errno) << std::endl;
					}
				}

			}
			// Send to broadcast
			if(msg.getMessageType() ==  Message::MessageType::JOIN || msg.getMessageType() ==  Message::MessageType::BYE || msg.getMessageType() ==  Message::MessageType::MSG || msg.getMessageType() ==  Message::MessageType::AUTH) {
				
				
				// seg.fault je tu v ruadkU:
				std::vector<User*> broadcastUsers = relationship->getUsersForChannel(channels->findChannel("default"));
				// takze chyba je v tomto: `relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel()`
				// dalsi seqfault je v BYE senderi
				//std::vector<User*> broadcastUsers = relationship->getUsersForChannel(relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel());
				/*UserChannelRelationship *rel = relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID));
				if(rel == nullptr) {
					*rel = UserChannelRelationship(users->findUserByUniqueID(currentClientID), channels->findChannel("default"));
				}
				std::vector<User*> broadcastUsers = relationship->getUsersForChannel(rel->getChannel());*/

				
				if(broadcastUsers.size() > 0) {
					// Iterate through all connected clients
					for (const auto& client : connectedClients) {

						// If AUTH, change message
						if(msg.getMessageType() == Message::MessageType::AUTH) {
							responseMessage = "MSG FROM Server IS ";
							responseMessage += users->findUserByUniqueID(currentClientID)->getDisplayname();
							responseMessage += " joined ";
							responseMessage += relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel()->getChannelID();
							responseMessage += ".";
							responseMessage += "\r\n";
						}
						else if(msg.getMessageType() == Message::MessageType::BYE) {
							responseMessage = "MSG FROM Server IS ";
							responseMessage += users->findUserByUniqueID(currentClientID)->getDisplayname();
							responseMessage += " has left ";
							responseMessage += relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel()->getChannelID();
							responseMessage += ".";
							responseMessage += "\r\n";
						}

						bool isBroadcastUser = std::any_of(broadcastUsers.begin(), broadcastUsers.end(),
							[client](const User* user) { return user->getUniqueID() == client.first; });

					
						if (isBroadcastUser) {
							if(responseMessage.empty() || (client.first == currentClientID && (msg.getMessageType() ==  Message::MessageType::MSG || msg.getMessageType() ==  Message::MessageType::BYE))) {}
							else {
								int broadcastSocket = client.second;
								int bytesSent = send(broadcastSocket, responseMessage.c_str(), responseMessage.length(), 0);
								if (bytesSent == -1) {
									std::cerr << "Error sending broadcast message: " << strerror(errno) << std::endl;
								}
							}
						}
					}
				}
			}
			if (msg.getMessageType() == Message::MessageType::BYE) {
				User *clientToRemove = users->findUserByUniqueID(currentClientID);
				relationship->removeRelationshipByUser(users->findUserByUniqueID(currentClientID));
				users->removeUser(clientToRemove->getUsername()); 
				connectedClients.erase(clientSocket);
				close(clientSocket);
				fds.erase(fds.begin() + i); // Remove from poll structure
			}

		  }
		}
	  }

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

	// Close the listening socket (important on program termination)
	close(socketDescriptor_);
	return true;
}