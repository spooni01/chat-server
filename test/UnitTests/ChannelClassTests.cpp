// is included in ChannelFactoryClass.cpp
// #include "../../src/Classes/Channel/Channel.cpp"
 
TEST(ChannelClassTests, CreationOfChannel) { 
	Channel channel("default");

	EXPECT_EQ(channel.getChannelID(), "default");
}

TEST(ChannelClassTests, InvalidChannelName) {
	Channel channel("x");

	EXPECT_EQ(channel.isChannelIDFormatCorrect("454$$@#R"), false);
}
