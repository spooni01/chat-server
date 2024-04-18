/**
 *	@file	Classes/FiniteStateMachine/FiniteStateMachine.hpp
 *	@brief	Finite state machine header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */


#ifndef FINITESTATEMACHINE_HPP
#define FINITESTATEMACHINE_HPP

// Libraries
#include <string>

// ANSI color codes
#define ANSI_COLOR_GREEN "\033[0;32m"	// help
#define ANSI_COLOR_ORANGE "\033[0;33m"	// warning
#define ANSI_COLOR_RED "\033[0;31m"		// error
#define ANSI_COLOR_RESET "\033[0m"		// reset


/**
 *  @class FiniteStateMachine
 *  This class works with finite state machine separately for each User
 */
class FiniteStateMachine {
public:

    /**
     *  @enum State
     *  States of finite state machine.
     */
    enum class State {
        NONE,
        ACCEPT,
        AUTH,
        OPEN,
        ERROR,
        END
    };


    /**
	 *  @brief	Function transfer State to ACCEPT.
	 */
    void transitionToAccept();


    /**
	 *  @brief	Function transfer State to AUTH.
	 */
    void transitionToAuth();


    /**
	 *  @brief	Function transfer State to OPEN.
	 */
    void transitionToOpen();


    /**
	 *  @brief	Function transfer State to ERROR.
	 */
    void transitionToError();


    /**
	 *  @brief	Function transfer State to END.
	 */
    void transitionToEnd();

    
    /**
	 *  @brief	Function return current State.
     *  @return Current state.
	 */
    State getState() const;


private:

    /**
	 *  @brief	Current state of finite state machine.
	 */
    State currentState = State::NONE;

};

#endif // FINITESTATEMACHINE_HPP