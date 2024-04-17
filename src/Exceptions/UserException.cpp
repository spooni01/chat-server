/**
 *	@file   Exceptions/UserException.cpp
 *	@brief  Exception class for invalid arguments.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef USEREXCEPTION_HPP
#define USEREXCEPTION_HPP

#include <iostream>
#include <string>


/**
 *  @class UserException
 *  This class represents an exception that is thrown when error occurs in User class.
 */
class UserException : public std::exception{
private:

    /**
     *  @brief The error message.
     */
    std::string message = "Problem with user.";

public:

    /**
     *  @brief Constructor for class.
     *  @param message The error message.
     */
    UserException(const std::string& message) : message(message) {}

    /**
     *  @brief Overrides the what() function from std::exception.
     *  @return The error message.
     */
    const char* what() const noexcept override { return message.c_str(); }

};

#endif // USEREXCEPTION_HPP
