
/**
 *	@file	test/ClientRequestProcessor/ClientRequestProcessor.cpp
 *	@brief	ClientRequestProcessor class header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef CLIENTREQUESTPROCESSOR_HPP
#define CLIENTREQUESTPROCESSOR_HPP

// Libraries
#include "../Message/Message.hpp"
#include "../UserFactory/UserFactory.hpp"
#include "../UserChannelRelationshipFactory/UserChannelRelationshipFactory.hpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class ClientRequestProcessor
 *  This class process client request.
 */
class ClientRequestProcessor {
private:
	std::string messageTCP;
public:
    
	ClientRequestProcessor(Message *message, UserFactory *users, int currentClientID, UserChannelRelationshipFactory *relationship, ChannelFactory *channels, std::string *globalErrMsg);
	std::string getMessageTCP();
};

#endif // CLIENTREQUESTPROCESSOR_HPP