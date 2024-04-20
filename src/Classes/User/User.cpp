/**
 *	@file	Classes/User/User.cpp
 *	@brief	User class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "User.hpp"


/**
 *  @brief	Constructor for class.
 *	@param	username Unique username of user.
 *	@param	displayname Display name of user.
 *	@param	secret Secret key of username
 */
User::User(std::string username, std::string displayname, std::string secret, int uniqueID) {

    // Checks
    if(!isUsernameFormatCorrect(username))
        throw UserException("Username has wrong syntax.");
    if(!isSecretFormatCorrect(secret))
        throw UserException("Secret has wrong syntax.");
    if(!isDisplaynameFormatCorrect(displayname))
        throw UserException("Displayname has wrong syntax.");

	// Code to checks secret correction can go in this place

    // Set variables
    this->username = username;
    this->displayname = displayname;
	this->uniqueID = uniqueID;
	this->state.transitionToAccept();

}


/**
 *  @brief	Checks if username is correct.
 *	@param	username username to check.
 *  @return true if syntax is correct.
 */
bool User::isUsernameFormatCorrect(const std::string& username) {

	// Check length
	if (username.length() > 20) {
		return false;
	}

	// Check characters
	for (char c : username) {
		if (!(std::isalnum(c) || c == '-')) {
			return false;
		}
	}

	return true;

}


/**
 *  @brief	Checks if secret is correct.
 *	@param	secret checks if secret has correct syntax.
 *  @return true if syntax is correct.
 */
bool User::isSecretFormatCorrect(const std::string& secret) {

	// Check length
	if (secret.length() > 128) {
		return false;
	}

	// Check characters
	for (char c : secret) {
		if (!(std::isalnum(c) || c == '-')) {
			return false;
		}
	}

	return true;

}


/**
 *  @brief	Checks if display name is correct.
 *	@param	displayname checks if display name has correct syntax.
 *  @return true if syntax is correct.
 */
bool User::isDisplaynameFormatCorrect(const std::string& displayname) {

	// Check length
	if (displayname.length() > 20) {
		return false;
	}

	// Check characters
	for (char c : displayname) {
		if (c < 0x21 || c > 0x7E) {
			return false;
		}
	}

	return true;

}


/**
 *  @brief	Returns username.
 *  @return username.
 */
std::string User::getUsername() const {

	if(!this->username.empty()) 
    	return this->username;
	else
		return "";

}


/**
 *  @brief	Returns display name.
 *  @return display name.
 */
std::string User::getDisplayname() const {

    return this->displayname;

}


/**
 *  @brief	Returns unique ID. It is used for communication.
 *  @return unique ID.
 */
int User::getUniqueID() const {

    return this->uniqueID;

}


