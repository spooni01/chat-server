/**
 *	@file	Classes/UserChannelRelationshipFactory/UserChannelRelationshipFactory.hpp
 *	@brief	UserChannelRelationshipFactory header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef USERCHANNELRELATIONSHIPFACTORY_HPP
#define USERCHANNELRELATIONSHIPFACTORY_HPP

// Libraries
#include <iostream>
#include <vector>
#include "../UserChannelRelationship/UserChannelRelationship.hpp"

// Exceptions
#include "../../Exceptions/ChannelException.cpp"
#include "../../Exceptions/UserException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class UserChannelRelationshipFactory
 *  This class creates and handles relationships beetwen user and channel
 */
class UserChannelRelationshipFactory {
private:

	/**
	 *  @brief	List of current relationships.
	 */
    std::vector<UserChannelRelationship> listOfRelationships;

public:

    /**
 	 *  @brief	Add relationship to listOfRelationships.
     *  @param  user Unique username in new relationship.
     *  @param  channelID Unique channelID in new relationship.
     */
	void addNewRelationship(User* user, Channel* channelID);

    /**
 	 *  @brief	Remove relationship from listOfRelationships.
     *  @param  user Unique username in relationship to remove.
     */
	void removeRelationshipByUser(User* user);

    /**
     *  @brief	Checks if relationship exists.
     *  @param  user Unique username in a relationship.
     *  @param  channelID Unique channelID in a relationship.
     *  @return true when relationship exists.
     */
    bool relationshipExists(User* user, Channel* channelID);

    /**
     *  @brief	Find channel in listOfChannels.
     *  @param  user Unique username in a relationship.
     *  @return pointer on relationship.
     */
    UserChannelRelationship* findRelationshipByUser(User* user);

    /**
	 * @brief Get a list of Users for a specific channel ID
	 * 
	 * @param channelID The channel ID
	 * @return A vector containing User objects (empty if no users found)
	 */
	std::vector<User*> getUsersForChannel(Channel* channelID);

};

#endif // USERCHANNELRELATIONSHIPFACTORY_HPP