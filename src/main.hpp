/**
 *	@file main.hpp
 *	@brief Main header file
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

// Include libraries
#include <iostream>

// Exceptions
#include "Exceptions/ArgumentException.cpp"
#include "Exceptions/ChannelException.cpp"
#include "Exceptions/UserException.cpp"

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset

// Include classes
#include "Classes/Arguments/Arguments.cpp"
#include "Classes/ChannelFactory/ChannelFactory.cpp"
#include "Classes/User/User.cpp"
#include "Classes/UserChannelRelationship/UserChannelRelationship.cpp"
