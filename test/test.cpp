#include <gtest/gtest.h>
#include "ArgumentsClassTests.cpp"
#include "ChannelFactoryClassTests.cpp"
#include "ChannelClassTests.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
