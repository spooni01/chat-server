/**
 *	@file main.cpp
 *	@brief Main file
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "main.hpp"


/**
 *	@brief	Main function
 *	@param	argc Number of parameters
 *	@param	argv Parameters
 *	@return	`0` on success, error code (1 to infinity) on error
 *	@throws	todo
 */
int main(int argc, char* argv[])
{

	std::cout << "Number of arguments: " << argc << std::endl;

	for (int i = 0; i < argc; ++i) {
		std::cout << "Argument " << i+1 << ": " << argv[i] << std::endl;
	}

	return 0;

}
