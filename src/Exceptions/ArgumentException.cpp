/**
 *	@file   Exceptions/ArgumentException.cpp
 *	@brief  Exception class for invalid arguments.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include <iostream>
#include <string>

/**
 *  @class ArgumentException
 *  This class represents an exception that is thrown when an invalid argument is provided to a program.
 *  It provides an error code and a message to describe the error condition.
 */
class ArgumentException : public std::exception {
private:

    /**
     *  @brief The error message.
     */
    std::string message = "Problem with arguments.";

public:

    /**
     *  @brief Constructor for class.
     *  @param message The error message.
     */
    ArgumentException(const std::string& message) : message(message) {}

    /**
     *  @brief Overrides the what() function from std::exception.
     *  @return The error message.
     */
    const char* what() const noexcept override { return message.c_str(); }

};
