/**
 *	@file	Classes/Channel/Channel.hpp
 *	@brief	Channel header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

// Libraries
#include <iostream>

// Exceptions
#include "../../Exceptions/ChannelException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class Channel
 *  This class works with channel
 */
class Channel {
private:

	/**
	 *  @brief	ID of channel.
	 */
	std::string channelID = "";

public:

	/**
	 *  @brief	Constructor for class, checks if @param channelID has correct syntax value.
	 *	@param	channelID Unique ID of channel.
	 */
	Channel(std::string channelID);

    /**
 	 *  @brief	Checks if format of channelID is correct.
     *  @param  channelID ID of channel to check.
     *  @return true if format is correct
     */
	bool isChannelIDFormatCorrect(std::string channel);

    /**
	 *  Getter functions
	 */ 
	/**
	 *  @brief	Returns channel ID.
	 *  @return channel ID.
	 */
	std::string getChannelID() const;

};

#endif // CHANNEL_HPP