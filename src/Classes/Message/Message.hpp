/**
 *	@file	Classes/Message/Message.hpp
 *	@brief	Message header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

// Libraries
#include <iostream>
#include <string>
#include <unordered_map>

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 * @class Message
 * @brief This class represents a message and provides functions for parsing it and extracting data.
 */
class Message {
public:

	/**
	 * Enumeration defining possible message types.
	 */
	enum class MessageType {
		INVALID,  ///< Invalid message format
		ERR,	 ///< Error message: "ERR FROM {DisplayName} IS {MessageContent}\r\n"
		REPLY,   ///< Reply message: "REPLY {"OK"|"NOK"} IS {MessageContent}\r\n"
		AUTH,	///< Authentication message: "AUTH {Username} AS {DisplayName} USING {Secret}\r\n"
		JOIN,	///< Join message: "JOIN {ChannelID} AS {DisplayName}\r\n"
		MSG,	 ///< Message from a user: "MSG FROM {DisplayName} IS {MessageContent}\r\n"
		BYE,	 ///< User disconnection message: "BYE\r\n"
		CONFIRM  ///< Unused message type in TCP communication
	};

	/**
	 * @brief Parses a message string in TCP format and stores the extracted data in the object.
	 * @param message The message string to parse.
	 */
	void parseTCP(const std::string& message);

	/**
	 * @return The message type.
	 */
	MessageType getMessageType() const;

	/**
	 * @return The message ID.
	 */
	std::string getMessageID() const;

	/**
	 * @return The username associated with the message.
	 */
	std::string getUsername() const;

	/**
	 * @return The channel ID associated with the message.
	 */
	std::string getChannelID() const;

	/**
	 * @return The secret key used for authentication (in AUTH message only).
	 */
	std::string getSecret() const;

	/**
	 * @return The user's display name.
	 */
	std::string getDisplayName() const;

	/**
	 * @return The content of the message.
	 */
	std::string getMessageContent() const;

	/**
	 * @return The content of the replyOKNOK.
	 */
	std::string getReplyOKNOK() const;
	

private:

	MessageType messageType;  ///< The type of the message
	std::string messageID = "";	///< Unique identifier for the message (optional)
	std::string username = "";	///< Username associated with the message (optional)
	std::string channelID = "";   ///< Channel ID associated with the message (optional)
	std::string secret = "";	  ///< Secret key used for authentication (AUTH message only)
	std::string displayName = ""; ///< User's display name (optional)
	std::string messageContent = "";///< Content of the message (optional)
	std::string replyOKNOK = "";///< Store reply NOK / OK.

};

#endif // MESSAGE_H