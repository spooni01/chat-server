/**
 *	@file main.hpp
 *	@brief Main header file
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

// Include libraries
#include <iostream>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <string>
#include <poll.h>
#include <csignal>

// Exceptions
#include "Exceptions/ArgumentException.cpp"
#include "Exceptions/ChannelException.cpp"
#include "Exceptions/UserException.cpp"
#include "Exceptions/NetworkException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset

// Include classes
#include "Classes/Arguments/Arguments.cpp"
#include "Classes/FiniteStateMachine/FiniteStateMachine.cpp"
#include "Classes/ChannelFactory/ChannelFactory.cpp"
#include "Classes/UserFactory/UserFactory.cpp"
#include "Classes/Message/Message.cpp"
#include "Classes/ClientRequestProcessor/ClientRequestProcessor.cpp"
#include "Classes/UserChannelRelationshipFactory/UserChannelRelationshipFactory.cpp"
#include "Classes/NetworkHandlers/TCPProtocolHandler/TCPProtocolHandler.cpp"
#include "Classes/NetworkHandlers/UDPProtocolHandler/UDPProtocolHandler.cpp"

