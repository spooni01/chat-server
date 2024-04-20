/**
 *	@file	Classes/Message/Message.cpp
 *	@brief	Message class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "Message.hpp"


/**
 * @brief Parses a message string in TCP format and stores the extracted data in the object.
 * @param message The message string to parse.
 */
void Message::parseTCP(const std::string& message) {

    // Check message type based on keywords
    if (message.find("AUTH ") == 0 && message.find(" AS ") != std::string::npos
        && message.find(" USE ") != std::string::npos) {
        this->messageType = MessageType::AUTH;
    }
    else if (message.find("ERR FROM ") == 0 && message.find(" IS ") != std::string::npos) {
        this->messageType = MessageType::ERR;
    }
    else if (message.find("REPLY ") == 0 && message.find(" IS ") != std::string::npos) {
        this->messageType = MessageType::REPLY;
    }
    else if (message.find("JOIN ") == 0 && message.find(" AS ") != std::string::npos) {
        this->messageType = MessageType::JOIN;
    }
    else if (message.find("MSG FROM ") == 0 && message.find(" IS ") != std::string::npos) {
        this->messageType = MessageType::MSG;
    }
    else if (message.find("BYE") == 0) {
        this->messageType = MessageType::BYE;
    }
    else {
        this->messageType = MessageType::INVALID; // Invalid message type
    }

    // Extract parameters based on message type
    switch (this->messageType) {
        case MessageType::AUTH: {
            size_t startPos = 5; // Skip "AUTH "
            size_t endPos = message.find(" AS ", startPos);
            if (endPos == std::string::npos) {
                this->messageType = Message::MessageType::INVALID;
                return; 
            }
            this->username = message.substr(startPos, endPos - startPos);

            startPos = endPos + 4; // Skip " AS "
            endPos = message.find(" USE ", startPos);
            if (endPos == std::string::npos) {
                this->messageType = Message::MessageType::INVALID;
                return; 
            }
            this->displayName = message.substr(startPos, endPos - startPos);

            startPos = endPos + 5; // Skip " USE "
            this->secret = message.substr(startPos);
            break;
        }
        case MessageType::ERR: {
            size_t startPos = 9; // Skip "ERR FROM "
            size_t endPos = message.find(" IS ", startPos);
            if (endPos == std::string::npos) {
                this->messageType = Message::MessageType::INVALID;
                return; 
            }
            this->displayName = message.substr(startPos, endPos - startPos);

            startPos = endPos + 4; // Skip " IS "
            this->messageContent = message.substr(startPos);
            break;
        }
        case MessageType::REPLY: {
            size_t startPos = 6; // Skip "REPLY "
            size_t endPos = message.find(" IS ", startPos);
            if (endPos == std::string::npos) {
                this->messageType = Message::MessageType::INVALID;
                return; 
            }
            this->replyOKNOK = message.substr(startPos, endPos - startPos);

            startPos = endPos + 4; // Skip " IS "
            this->messageContent = message.substr(startPos);
            break;
        }
        case MessageType::JOIN: {
            size_t startPos = 5; // Skip "JOIN "
            size_t endPos = message.find(" AS ", startPos);
            if (endPos == std::string::npos) {
                this->messageType = Message::MessageType::INVALID;
                return; 
            }
            this->channelID = message.substr(startPos, endPos - startPos);

            startPos = endPos + 4; // Skip " AS "
            this->displayName = message.substr(startPos);
            break;
        }
        case MessageType::MSG: {
            size_t startPos = 9; // Skip "MSG FROM "
            size_t endPos = message.find(" IS ", startPos);
            if (endPos == std::string::npos) {
                this->messageType = Message::MessageType::INVALID;
                return; 
            }
            this->displayName = message.substr(startPos, endPos - startPos);

            startPos = endPos + 4; // Skip " IS "
            this->messageContent = message.substr(startPos);
            break;
        }
        case MessageType::BYE:
            break;
        default: {
            // Shouldn't happen, but handle unexpected type for safety
            this->messageType = Message::MessageType::INVALID;
            return; 
        }
    }
}


/**
 * @return The message type.
 */
Message::MessageType Message::getMessageType() const {

    return this->messageType;

}


/**
 * @return The message ID.
 */
std::string Message::getMessageID() const {

    return this->messageID;

}


/**
 * @return The username associated with the message.
 */
std::string Message::getUsername() const {

    return this->username;

}


/**
 * @return The channel ID associated with the message.
 */
std::string Message::getChannelID() const {

    return this->channelID;

}


/**
 * @return The secret key used for authentication (in AUTH message only).
 */
std::string Message::getSecret() const  {

    return this->secret;

}


/**
 * @return The user's display name.
 */
std::string Message::getDisplayName() const  {

    return this->displayName;

}


/**
 * @return The content of the message.
 */
std::string Message::getMessageContent() const {

    return this->messageContent;

}


/**
 * @return The content of the replyOKNOK.
 */
std::string Message::getReplyOKNOK() const {

    return this->replyOKNOK;

}
