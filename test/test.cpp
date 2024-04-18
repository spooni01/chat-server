#include <gtest/gtest.h>
#include "ArgumentsClassTests.cpp"
#include "ChannelFactoryClassTests.cpp"
#include "ChannelClassTests.cpp"
#include "UserFactoryClassTests.cpp"
#include "UserClassTests.cpp"
#include "UserChannelRelationshipFactoryTests.cpp"
#include "UserChannelRelationshipTests.cpp"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
