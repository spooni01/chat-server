/**
 *	@file	Classes/User/User.hpp
 *	@brief	User header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef USER_HPP
#define USER_HPP

// Libraries
#include <iostream>

// Exceptions
#include "../../Exceptions/UserException.cpp"
#include "../FiniteStateMachine/FiniteStateMachine.hpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class User
 *  This class works with user
 */
class User {
private:

	/**
	 *  @brief	Username of user.
	 */
	std::string username;

	/**
	 *  @brief	Get unique ID.
	 */
	int uniqueID;

public:

	/**
	 *  @brief	Display name of user.
	 */
	std::string displayname;

	/**
	 *  @brief	State of user
	 */
	FiniteStateMachine state;

	/**
	 *  @brief	Constructor for class.
	 *	@param	channelID Unique ID of channel.
	 */
	User(std::string username, std::string displayname, std::string secret, int uniqueID = -1);

	/**
	*	@brief	Checks if username is correct.
	*	@param	username username to check.
	*/
	bool isUsernameFormatCorrect(const std::string& username);

	/**
	*	@brief	Checks if secret is correct.
	*	@param	secret checks if secret has correct syntax.
	*	@return true if syntax is correct.
	*/
	bool isSecretFormatCorrect(const std::string& secret);

	/**
	*  @brief	Checks if display name is correct.
	*	@param	displayname checks if display name has correct syntax.
	*  @return true if syntax is correct.
	*/
	bool isDisplaynameFormatCorrect(const std::string& displayname);

	/**
	 *  Getter functions
	 */ 
	/**
	 *  @brief	Returns username.
	 *  @return username.
	 */
	std::string getUsername() const;

	/**
	 *  @brief	Returns display name.
	 *  @return display name.
	 */
	std::string getDisplayname() const;

	/**
	 *  @brief	Returns unique ID. It is used for communication.
	 *  @return unique ID.
	 */
	int getUniqueID() const;

};

#endif // USER_HPP