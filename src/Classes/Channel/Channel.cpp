/**
 *	@file	Classes/Channel/Channel.cpp
 *	@brief	Channel class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "Channel.hpp"


/**
 *  @brief	Constructor for class, checks if @param channelID has correct syntax value.
 *	@param	channelID Unique ID of channel.
 */
Channel::Channel(std::string channelID) {

    if(!this->isChannelIDFormatCorrect(channelID))
        std::string globalErrMsg = "ChannelID is incorrect.";
    
    this->channelID = channelID;

}


/**
 *  @brief	Checks if format of channelID is correct.
 *  @return true if format is correct
 */
bool Channel::isChannelIDFormatCorrect(std::string channel) {

    // Check length
	if (channel.length() > 20) {
		return false;
	}

	// Check characters
	for (char c : channel) {
		if (!(std::isalnum(c) || c == '-' || c == '.')) {
			return false;
		}
	}

	return true;

}


/**
 *  @brief	Returns channel ID.
 *  @return channel ID.
 */
std::string Channel::getChannelID() const {

    return this->channelID;

}
