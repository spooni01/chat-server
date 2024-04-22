/**
 *	@file	main.cpp
 *	@brief	Main file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "main.hpp"


/**
 *	@brief	Main function.
 *	@param	argc Number of parameters.
 *	@param	argv Parameters.
 *	@return	`0` on success, error code (1 to infinity) on error.
 *	@throws	ArgumentException when problem in a Arguments class
 *	@throws	ChannelException when problem in a Channel or ChannelFactory class
 *	@throws	UserException when problem in a User or UserFactory class
 */
int main(int argc, char* argv[])
{

	try {
		
		// Set variables
		Arguments arguments(argc, argv); 				// Parse arguments.
		ChannelFactory channels;		 				// Handle operations with channels.
		UserFactory users;								// Handle operations with users.
		UserChannelRelationshipFactory relationships;	// Handle relationships beetwen user and channel (which user is in which channel).
		TCPProtocolHandler tcp(arguments.getServerIpAddress(), arguments.getPort());	// Incoming TCP communication handler

		// Listen for sockets and handle it inside functions
		tcp.listenForSockets(&users, &relationships, &channels);

	} catch (const ArgumentException &e) {
		std::cerr << ANSI_COLOR_RED << "Exception caught: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 10;
	} catch (const ChannelException &e) {
		std::cerr << ANSI_COLOR_RED << "Exception caught: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 20;
	} catch (const UserException &e) {
		std::cerr << ANSI_COLOR_RED << "Exception caught: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 30;
	} catch (const NetworkException &e) {
		std::cerr << ANSI_COLOR_RED << "Exception caught: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 40;
	} catch (const std::length_error &e) {
		std::cerr << ANSI_COLOR_RED << "Exception creationg string: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 50;
	} catch (const std::bad_alloc &e) {
		std::cerr << ANSI_COLOR_RED << "Exception bad allocation: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 51;
	}

	return 0;

}
