#include "../../src/Classes/FiniteStateMachine/FiniteStateMachine.cpp"
 
TEST(FiniteStateMachineClassTests, CreationOfFiniteStateMachine) { 
	FiniteStateMachine fsm;

	EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::NONE);
}

TEST(FiniteStateMachineClassTests, TransitionsToStates) {
	FiniteStateMachine fsm;
	EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::NONE);
    
    EXPECT_NO_THROW(fsm.transitionToAccept());
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::ACCEPT);

    EXPECT_NO_THROW(fsm.transitionToAuth());
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::AUTH);

    EXPECT_NO_THROW(fsm.transitionToOpen());
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::OPEN);

    EXPECT_NO_THROW(fsm.transitionToError());
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::ERROR);

    EXPECT_NO_THROW(fsm.transitionToEnd());
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::END);
}
