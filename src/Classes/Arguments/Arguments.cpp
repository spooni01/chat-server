/**
 *	@file	main.hpp
 *	@brief	Arguments class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "Arguments.hpp"


/**
 *	@brief	Constructor for class.
 *	@param	argc Number of parameters.
 *	@param	argv Parameters.
 */
Arguments::Arguments(int argc, char* argv[]) : serverIpAddress("0.0.0.0"), serverPort(4567), timeout(250), retransmissions(3)	{

	int option;
	while ((option = getopt(argc, argv, "hl:p:d:r:")) != -1) {
		switch (option) {
			case 'h':
				// Help option
				printHelp();
				exit(0);
			case 'l':
				// Server IP
				if (!this->isValidIPv4Format(optarg))
					throw ArgumentException("Server IP addres is not in IPv4 format.");
				else
					this->serverIpAddress = optarg;
				break;
			case 'p':
				// Port option
				if (std::stoi(optarg) > 65535 || std::stoi(optarg) < 0)
					throw ArgumentException("Port must be beetwen 0 and 65535");
				else
					this->serverPort = std::atoi(optarg);
				break;
			case 'd':
				// Timeout option
				this->timeout = std::atoi(optarg);
				break;
			case 'r':
				// Retransmissions option
				this->retransmissions = std::atoi(optarg);
				break;
			default:
				// Invalid option
				std::stringstream msg;
				throw ArgumentException("Invalid argument option");
		}
	}

}


/**
 *	@brief Function to print help message on STDOUT.
 */
void Arguments::printHelp() const {

	std::cout << ANSI_COLOR_GREEN << "Usage: ipk24chat-server [-s server ip] [-p server port] [-d UDP timeout] [-r UDP retransmissions]" << ANSI_COLOR_RESET << std::endl;

}


/**
 *	@brief Returns server IP address.
 *	@return Server IP address.
 */
std::string Arguments::getServerIpAddress() const
{

	return this->serverIpAddress;

}


/**
 *	@brief Returns server port.
 *	@return Server port.
 */
uint16_t Arguments::getPort() const
{

	return this->serverPort;

}


/**
 *	@brief Returns UDP confirmation timeout.
 *	@return UDP timeout.
 */
uint16_t Arguments::getTimeout() const
{

	return this->timeout;

}


/**
 *	@brief Returns numbert of UDP retransmissions.
 *	@return UDP retransmissions.
 */
uint8_t Arguments::getRetransmissions() const
{

	return this->retransmissions;

}


/**
 *	@brief	Checks if ipAddress is address of IPv4.
 *	@param	ipAddress IP address to be checks if it is correct.
 *	@return true if ipAddress is in correct IPv4 format.
 */
bool Arguments::isValidIPv4Format(const std::string& ipAddress)
{
	
	// Split the string by dots
	std::istringstream ss(ipAddress);
	std::string token;

	int parts = 0;
	while (std::getline(ss, token, '.') && parts < 4) {
		int numValue;
		// Try converting the token to a number
		if (std::stringstream(token) >> numValue) {
			
			// Check if the value is within range (0-255)
			if (numValue >= 0 && numValue <= 255)
				parts++;
			else
				return false; 
			
		}
		else {
			return false; // Non-numeric token
		}
	}

	// Check if there is exactly 4 parts
	if(parts == 4)
		return true;
	else
		return false;

}