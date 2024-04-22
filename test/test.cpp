#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "UnitTests/ArgumentsClassTests.cpp"
#include "UnitTests/ChannelFactoryClassTests.cpp"
#include "UnitTests/ChannelClassTests.cpp"
#include "UnitTests/FiniteStateMachineClassTests.cpp"
#include "UnitTests/MessageClassTests.cpp"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
