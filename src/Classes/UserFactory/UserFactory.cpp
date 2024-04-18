/**
 *	@file	Classes/UserFactory/UserFactory.cpp
 *	@brief	UserFactory class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "../User/User.cpp"
#include "UserFactory.hpp"



/**
 *  @brief	Add user to listOfUsers.
 *	@param	username Unique username of user.
 *	@param	displayname Display name of user.
 *	@param	secret Secret key of username.
*/
void UserFactory::addNewUser(std::string username, std::string displayname, std::string secret) {

	User tmp(username, displayname, secret);
	this->listOfUsers.push_back(tmp);

}


/**
 *  @brief	Remove channel from listOfUsers
 *  @param  username Unique username of user to remove.
 */
void UserFactory::removeUser(std::string username) {

	listOfUsers.erase(
		std::remove_if(this->listOfUsers.begin(), this->listOfUsers.end(),
		[username](const User& user) {
			return user.getUsername() == username;
		}),
		this->listOfUsers.end());

}


/**
 *  @brief	Checks if user exists.
 *  @param  username Unique username to check.
 *  @return true when user exists.
 */
bool UserFactory::userExists(std::string username) {

	return std::any_of(listOfUsers.begin(), listOfUsers.end(),
		[username](const User& user) {
			return user.getUsername() == username;
		});

}


/**
 *  @brief	Find user in listOfUsers.
 *  @param  username Unique username of user to find.
 *  @return pointer on user.
 */
User* UserFactory::findUser(std::string username) {

  	auto foundUser = std::find_if(listOfUsers.begin(), listOfUsers.end(),
    	[username](const User& user) {
        	return user.getUsername() == username;
    });

  	if (foundUser != listOfUsers.end()) 
    	return &(*foundUser);
	else 
    	return nullptr;

}