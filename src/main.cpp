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
 */
int main(int argc, char* argv[])
{

	try {

		Arguments arguments(argc, argv); // Parse arguments

	} catch (const ArgumentException &e) {
		std::cerr << ANSI_COLOR_RED << "Exception caught: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 10;
	} catch (const ChannelException &e) {
		std::cerr << ANSI_COLOR_RED << "Exception caught: " << e.what() << ANSI_COLOR_RESET << std::endl;
		return 20;
	}

	return 0;

}
