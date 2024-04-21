/**
 *	@file	Classes/ChannelFactory/ChannelFactory.hpp
 *	@brief	ChannelFactory header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef CHANNELFACTORY_HPP
#define CHANNELFACTORY_HPP

// Libraries
#include <iostream>
#include <vector>
#include "../Channel/Channel.hpp"
#include "../UserFactory/UserFactory.hpp"

// Exceptions
#include "../../Exceptions/ChannelException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class ChannelFactory
 *  This class creates and handles channels
 */
class ChannelFactory {
private:

	/**
	 *  @brief	List of current channels.
	 */
	std::vector<Channel> listOfChannels;

public:

	/**
	 *  @brief	Constructor for class, will add `default` to listOfChannels.
	 */
	ChannelFactory();

	/**
 	 *  @brief	Add channel to listOfChannels
	 *  @param  newChannelID ID of new channel to add to list of channels.
	 */
	void addNewChannel(std::string newChannelID);

	/**
 	 *  @brief	Remove channel from listOfChannelss
	 *  @param  channelId ID of channel to remove.
	 */
	void removeChannel(std::string channelId);

	/**
	 *  @brief	Checks if channel exists.
	 *  @param  channelId ID of channel to remove.
	 *  @return true when channel exists.
	 */
	bool channelExists(std::string channelID);

	/**
	 *  @brief	Find channel in listOfChannels.
	 *  @param  channelId ID of channel to find.
	 *  @return pointer on channel.
	 */
	Channel* findChannel(std::string channelID);

};

#endif // CHANNELFACTORY_HPP