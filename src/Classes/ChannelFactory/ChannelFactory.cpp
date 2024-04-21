/**
 *	@file	Classes/ChannelFactory/ChannelFactory.cpp
 *	@brief	ChannelFactory class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "../Channel/Channel.cpp"
#include "ChannelFactory.hpp"


/**
 *  @brief	Constructor for class, will add `default` to listOfChannels.
 */
ChannelFactory::ChannelFactory() {

	this->addNewChannel("default");

}


/**
 *  @brief	Add channel to list of channels
 *  @param  newChannelID ID of new channel to add to list of channels.
 */
void ChannelFactory::addNewChannel(std::string newChannelID) {

	this->listOfChannels.push_back(Channel(newChannelID));

}


/**
 *  @brief	Remove channel from listOfChannels. Default channel (`default`) will be never deleted.
 *  @param  channelId ID of channel to remove.
 */
void ChannelFactory::removeChannel(std::string channelId) {

	if(channelId != "default") { // Do not remove default channel
		listOfChannels.erase(
			std::remove_if(this->listOfChannels.begin(), this->listOfChannels.end(),
			[channelId](const Channel& channel) {
				return channel.getChannelID() == channelId;
			}),
			this->listOfChannels.end());
	}
}


/**
 *  @brief	Checks if channel exists.
 *  @param  channelId ID of channel to find.
 *  @return true when channel exists.
 */
bool ChannelFactory::channelExists(std::string channelID) {

	return std::any_of(listOfChannels.begin(), listOfChannels.end(),
		[channelID](const Channel& channel) {
			return channel.getChannelID() == channelID;
		});

}


/**
 *  @brief	Find channel in listOfChannels.
 *  @param  channelId ID of channel to find.
 *  @return pointer on channel.
 */
Channel* ChannelFactory::findChannel(std::string channelID) {

  	auto foundChannel = std::find_if(listOfChannels.begin(), listOfChannels.end(),
    	[channelID](const Channel& channel) {
        	return channel.getChannelID() == channelID;
    });

  	if (foundChannel != listOfChannels.end()) 
    	return &(*foundChannel);
	else 
    	return nullptr;

}
