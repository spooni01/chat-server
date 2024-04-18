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
User::User(std::string username, std::string displayname, std::string secret) {

    // Checks
    if(!isUsernameFormatCorrect(username))
        throw UserException("Username has wrong syntax.");
    if(!isSecretFormatCorrect(displayname))
        throw UserException("Secret has wrong syntax.");
    if(!isDisplaynameFormatCorrect(secret))
        throw UserException("Displayname has wrong syntax.");

	// Code to checks secret correction can go here, it is stored in `secret`

    // Set variables
    this->username = username;
    this->displayname = displayname;

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

    return this->username;

}


/**
 *  @brief	Returns display name.
 *  @return display name.
 */
std::string User::getDisplayname() const {

    return this->displayname;

}

