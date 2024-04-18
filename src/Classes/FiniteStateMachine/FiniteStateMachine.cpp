/**
 *	@file	Classes/FiniteStateMachine/FiniteStateMachine.cpp
 *	@brief	FiniteStateMachine class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "FiniteStateMachine.hpp"


/**
 *  @brief	Function transfer State to ACCEPT
 */
void FiniteStateMachine::transitionToAccept() {

    this->currentState = State::ACCEPT;

}


/**
 *  @brief	Function transfer State to AUTH
 */
void FiniteStateMachine::transitionToAuth() {

    this->currentState = State::AUTH;

}


/**
 *  @brief	Function transfer State to OPEN
 */
void FiniteStateMachine::transitionToOpen() {

    this->currentState = State::OPEN;

}


/**
 *  @brief	Function transfer State to ERROR
 */
void FiniteStateMachine::transitionToError() {

    this->currentState = State::ERROR;

}


/**
 *  @brief	Function transfer State to END
 */
void FiniteStateMachine::transitionToEnd() {

    this->currentState = State::END;

}



/**
 *  @brief	Function return current State
 */
FiniteStateMachine::State FiniteStateMachine::getState() const {

    return this->currentState;

}
