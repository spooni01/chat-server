/**
 *	@file	Classes/Arguments/Arguments.hpp
 *	@brief	Arguments header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

// Libraries
#include <iostream>
#include <cstdlib>
#include <getopt.h>
#include <string>
#include <sstream>

// Exceptions
#include "../../Exceptions/ArgumentException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class Arguments
 *  This class checks if arguments are correct and stores it.
 */
class Arguments {
private:

	/**
	 *  @brief	Server listening IP address for welcome sockets.
	 */
	std::string serverIpAddress;

	/**
	 *  @brief	Server listening port for welcome sockets.
	 */
	uint16_t serverPort;
		
	/**
	 *  @brief	UDP confirmation timeout.
	 */
	uint16_t timeout;

	/**
	 *  @brief	Maximum number of UDP retransmissions.
	 */
	uint8_t retransmissions;

public:

	/**
	 *  @brief	Constructor for class.
	 *	@param	argc Number of parameters.
	 *	@param	argv Parameters.
	 */
	Arguments(int argc, char* argv[]);

	/**
	 *  @brief	Function to print help message on STDOUT.
	 */
	void printHelp() const;


	/**
	 *  Getter functions
	 */ 
	/**
	 *  @brief	Returns server IP address.
	 *  @return Server IP address.
	 */
	std::string getServerIpAddress() const;

	/**
	 *  @brief	Returns server port.
	 *  @return Server port.
	 */
	uint16_t getPort() const;

	/**
	 *  @brief	Returns UDP confirmation timeout.
	 *  @return UDP timeout.
	 */
	uint16_t getTimeout() const;

	/**
	 *  @brief	Returns numbert of UDP retransmissions.
	 *  @return UDP retransmissions.
	 */
	uint8_t getRetransmissions() const;

	/**
	*	@brief	Checks if ipAddress is address of IPv4.
	*	@param	ipAddress IP address to be checks if it is correct.
	*	@return true if ipAddress is in correct IPv4 format.
	*/
	bool isValidIPv4Format(const std::string& ipAddress);

};

#endif // ARGUMENTS_HPP