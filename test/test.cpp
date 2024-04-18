#include <gtest/gtest.h>
#include "UnitTests/ArgumentsClassTests.cpp"
#include "UnitTests/ChannelFactoryClassTests.cpp"
#include "UnitTests/ChannelClassTests.cpp"
#include "UnitTests/UserFactoryClassTests.cpp"
#include "UnitTests/UserClassTests.cpp"
#include "UnitTests/UserChannelRelationshipFactoryTests.cpp"
#include "UnitTests/UserChannelRelationshipTests.cpp"
#include "UnitTests/FiniteStateMachineClassTests.cpp"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
