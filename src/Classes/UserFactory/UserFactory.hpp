/**
 *	@file	Classes/UserFactory/UserFactory.hpp
 *	@brief	UserFactory header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef USERFACTORY_HPP
#define USERFACTORY_HPP

// Libraries
#include <iostream>
#include <vector>
#include "../User/User.hpp"

// Exceptions
#include "../../Exceptions/UserException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class UserFactory
 *  This class creates and handles users. It also handles all connections.
 */
class UserFactory {
private:

	/**
	 *  @brief	List of current channels.
	 */
	std::vector<User> listOfUsers;

public:


	/**
 	 *  @brief	Add user to listOfUsers.
	 *	@param	username Unique username of user.
	 *	@param	displayname Display name of user.
	 *	@param	secret Secret key of username.
	*/
	void addNewUser(std::string username, std::string displayname, std::string secret, int currentClientID);

	/**
 	 *  @brief	Remove channel from listOfUsers
	 *  @param  username Unique username of user to remove.
	 */
	void removeUser(std::string username);

	/**
	 *  @brief	Checks if user exists.
	 *  @param  username Unique username to check.
	 *  @return true when user exists.
	 */
	bool userExists(std::string username);

	/*  @brief	Checks if user exists.
	 *  @param  username Unique username to check.
	 *  @return true when user exists.
	 */
	bool userExistsByUniqueID(int uniqueID);

	/**
	 *  @brief	Find user in listOfUsers.
	 *  @param  username Unique username of user to find.
	 *  @return pointer on user.
	 */
	User* findUser(std::string username);


	/**
	*  @brief	Find user  by unique id in listOfUsers.
	*  @param  username Unique username of user to find.
	*  @return pointer on user.
	*/
	User* findUserByUniqueID(int uniqueID);


	/**
	*  @brief  Counts the number of users in listOfUsers.
	*  @return The number of users.
	*/
	int getNumberOfUsers();

	/**
	 *  @brief  Removes all users from listOfUsers.
	 *
	 *	Used in tests.
	 */
	void removeAllUsers();

};

#endif // USERFACTORY_HPP