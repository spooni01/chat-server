#include "../src/Classes/Arguments/Arguments.cpp"
 
TEST(ArgumentsClassTest, NonDefinedArguments) { 
	Arguments arguments(1, NULL);

	EXPECT_EQ(arguments.getServerIpAddress(), "0.0.0.0");
	EXPECT_EQ(arguments.getPort(), 4567);
	EXPECT_EQ(arguments.getTimeout(), 250); 
	EXPECT_EQ(arguments.getRetransmissions(), 3); 
}

TEST(ArgumentsClassTest, BasicParsing) {
	const int testingArgc = 5;
	const char* testingArgv[] = {"ipk24chat-server", "-l", "192.168.1.10", "-p", "4444"};
	Arguments arguments(testingArgc, const_cast<char**>(testingArgv));

	EXPECT_EQ(arguments.getServerIpAddress(), "192.168.1.10");
	EXPECT_EQ(arguments.getPort(), 4444);
	EXPECT_EQ(arguments.getTimeout(), 250); 
	EXPECT_EQ(arguments.getRetransmissions(), 3); 
}