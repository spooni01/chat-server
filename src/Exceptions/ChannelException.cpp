/**
 *	@file   Exceptions/ChannelException.cpp
 *	@brief  Exception class for channel.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef CHANNELEXCEPTION_HPP
#define CHANNELEXCEPTION_HPP

#include <iostream>
#include <string>


/**
 *  @class ChannelException
 *  This class represents an exception that is thrown when
 *  working with channel.
 */
class ChannelException : public std::exception{
private:

    /**
     *  @brief The error message.
     */
    std::string message = "Problem with channel.";

public:

    /**
     *  @brief Constructor for class.
     *  @param message The error message.
     */
    ChannelException(const std::string& message) : message(message) {}

    /**
     *  @brief Overrides the what() function from std::exception.
     *  @return The error message.
     */
    const char* what() const noexcept override { return message.c_str(); }

};

#endif // CHANNELEXCEPTION_HPP
