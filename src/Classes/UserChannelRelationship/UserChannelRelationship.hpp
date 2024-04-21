/**
 *	@file	Classes/UserChannelRelationship/UserChannelRelationship.hpp
 *	@brief	UserChannelRelationship header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef USERCHANNELRELATIONSHIP_HPP
#define USERCHANNELRELATIONSHIP_HPP

// Libraries
#include <vector>
#include <string>

// Exceptions
#include "../../Exceptions/UserException.cpp"
#include "../../Exceptions/ChannelException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class UserChannelRelationship
 *  This class stores relationship beetwen user and channel (which user is in which channel)
 */
class UserChannelRelationship {
private:

	/**
	 *  @brief User in a relationship.
	 */
	User* user;

    /**
	 *  @brief Channel in a relationship.
	 */
	Channel* channel;

public:

	/**
	 *  @brief	Constructor for class.
	 *	@param	user User in a relationship.
     *	@param	channel Channel in a relationship.
	 */
	UserChannelRelationship(User* user, Channel* channel);

    /**
 	 *  @brief	Set channel.
     */
	void setChannel(Channel* newChannel);

    /**
 	 *  @brief	Get pointer to channel.
     *  @return Pointer to channel.
     */
	Channel* getChannel();

    /**
 	 *  @brief	Get pointer to user.
     *  @return Pointer to user.
     */
	User* getUser() const;

};

#endif // USERCHANNELRELATIONSHIP_HPP