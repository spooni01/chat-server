/**
 *	@file	Classes/UserChannelRelationshipFactory/UserChannelRelationshipFactory.cpp
 *	@brief	UserChannelRelationshipFactory class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "../UserChannelRelationship/UserChannelRelationship.cpp"
#include "UserChannelRelationshipFactory.hpp"


/**
 *  @brief	Add relationship to listOfRelationships.
 *  @param  user Unique username in new relationship.
 *  @param  channelID Unique channelID in new relationship.
 */
void UserChannelRelationshipFactory::addNewRelationship(User* user, Channel* channelID) {

	User *tmpUser = user;
	Channel *tmpChannel = channelID;


	UserChannelRelationship tmp(tmpUser, tmpChannel);
	this->listOfRelationships.push_back(tmp);

}


/**
 *  @brief	Remove relationship from listOfRelationships.
 *  @param  user Unique username in relationship to remove.
 */
void UserChannelRelationshipFactory::removeRelationshipByUser(User* user) {

	listOfRelationships.erase(
		std::remove_if(this->listOfRelationships.begin(), this->listOfRelationships.end(),
		[user](UserChannelRelationship& relationship) {
			return relationship.getUser() == user;
		}),
		this->listOfRelationships.end());

}


/**
 *  @brief	Checks if relationship exists.
 *  @param  user Unique username in a relationship.
 *  @param  channelID Unique channelID in a relationship.
 *  @return true when relationship exists.
 */
bool UserChannelRelationshipFactory::relationshipExists(User* user, Channel* channelID) {

	return std::any_of(listOfRelationships.begin(), listOfRelationships.end(),
		[user, channelID](UserChannelRelationship& relationship) {
			return relationship.getUser() == user && relationship.getChannel() == channelID;
		});

}


/**
 *  @brief	Find channel in listOfChannels.
 *  @param  user Unique username in a relationship.
 *  @return pointer on relationship.
 */
UserChannelRelationship* UserChannelRelationshipFactory::findRelationshipByUser(User* user) {

  	auto foundRelationship = std::find_if(listOfRelationships.begin(), listOfRelationships.end(),
		[user](UserChannelRelationship& relationship) {
			return relationship.getUser() == user;
	});

  	if (foundRelationship != listOfRelationships.end()) 
		return &(*foundRelationship);
	else {
		exit(222);
		return nullptr;
	}

}


/**
 * @brief Get a list of Users for a specific channel ID 
 * @param channelID The channel ID
 * @return A vector containing User objects (empty if no users found)
 */
std::vector<User*> UserChannelRelationshipFactory::getUsersForChannel(Channel* channelID) {
  std::vector<User*> users;
  for (auto& relationship : listOfRelationships) {
	if (relationship.getChannel()->getChannelID() == channelID->getChannelID()) {
	  users.push_back(relationship.getUser());
	}
  }
  return users;
}
