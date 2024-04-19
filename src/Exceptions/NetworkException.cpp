/**
 *	@file   Exceptions/NetworkException.cpp
 *	@brief  Exception class for network.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef NETWORKEXCEPTION_HPP
#define NETWORKEXCEPTION_HPP

#include <iostream>
#include <string>


/**
 *  @class NetworkException
 *  This class represents an exception that is thrown when
 *  working with channel.
 */
class NetworkException : public std::exception{
private:

    /**
     *  @brief The error message.
     */
    std::string message = "Problem with network.";

public:

    /**
     *  @brief Constructor for class.
     *  @param message The error message.
     */
    NetworkException(const std::string& message) : message(message) {}

    /**
     *  @brief Overrides the what() function from std::exception.
     *  @return The error message.
     */
    const char* what() const noexcept override { return message.c_str(); }

};

#endif // NETWORKEXCEPTION_HPP
