#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include "../src/Classes/Arguments/Arguments.hpp"
#include "../src/Classes/FiniteStateMachine/FiniteStateMachine.hpp"
#include "../src/Classes/ChannelFactory/ChannelFactory.hpp"
#include "../src/Classes/UserFactory/UserFactory.hpp"
#include "../src/Classes/Message/Message.hpp"
#include "../src/Classes/ClientRequestProcessor/ClientRequestProcessor.hpp"
#include "../src/Classes/UserChannelRelationshipFactory/UserChannelRelationshipFactory.hpp"
#include "../src/Classes/NetworkHandlers/TCPProtocolHandler/TCPProtocolHandler.hpp"
#include "../src/Classes/NetworkHandlers/UDPProtocolHandler/UDPProtocolHandler.hpp"

#include "ClientSimulator/TCPClientSimulator.cpp"
#include "UnitTests/ArgumentsClassTests.cpp"
#include "UnitTests/ChannelFactoryClassTests.cpp"
#include "UnitTests/ChannelClassTests.cpp"
#include "UnitTests/UserFactoryClassTests.cpp"
#include "UnitTests/UserClassTests.cpp"
#include "UnitTests/UserChannelRelationshipFactoryTests.cpp"
#include "UnitTests/UserChannelRelationshipTests.cpp"
#include "UnitTests/FiniteStateMachineClassTests.cpp"
#include "UnitTests/TCPProtocolHandlerClassTests.cpp"
#include "UnitTests/MessageClassTests.cpp"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
