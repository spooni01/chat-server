/**
 *	@file	Classes/UserChannelRelationship/UserChannelRelationship.cpp
 *	@brief	UserChannelRelationship class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "UserChannelRelationship.hpp"


/**
 *  @brief	Constructor for class.
 *	@param	user User in a relationship.
 *	@param	channel Channel in a relationship.
 */
UserChannelRelationship::UserChannelRelationship(User* user, Channel* channel) {

    this->user = user;
    this->channel = channel;

}


/**
 *  @brief	Set channel.
 */
void UserChannelRelationship::setChannel(Channel* newChannel) {

    this->channel = newChannel;

}


/**
 *  @brief	Get channel by user.
 *  @return Pointer to channel.
 */
Channel* UserChannelRelationship::getChannel() {

    return this->channel;

}


/**
 *  @brief	Get user by channel.
 *  @return Pointer to user.
 */
User* UserChannelRelationship::getUser() const {

    return this->user;

}
