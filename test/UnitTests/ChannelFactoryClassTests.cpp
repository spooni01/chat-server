#include "../../src/Classes/ChannelFactory/ChannelFactory.cpp"
 
TEST(ChannelFactoryClassTests, AddedNewChannel) { 
	ChannelFactory channelFactory;

    EXPECT_EQ(channelFactory.channelExists("default"), true);

	EXPECT_NO_THROW(channelFactory.addNewChannel("test1"));
    EXPECT_NO_THROW(channelFactory.addNewChannel("specialChannel"));

    EXPECT_EQ(channelFactory.channelExists("test1"), true);
    EXPECT_EQ(channelFactory.channelExists("specialChannel"), true);

}

TEST(ChannelFactoryClassTests, ChannelExists) {
	ChannelFactory channelFactory;

	EXPECT_NO_THROW(channelFactory.addNewChannel("test1"));
    EXPECT_EQ(channelFactory.channelExists("test1"), true);
}


TEST(ChannelFactoryClassTests, RemoveChannel) {
	ChannelFactory channelFactory;

	EXPECT_NO_THROW(channelFactory.addNewChannel("test1"));
    EXPECT_NO_THROW(channelFactory.addNewChannel("specialChannel"));
    EXPECT_EQ(channelFactory.channelExists("test1"), true);

    EXPECT_NO_THROW(channelFactory.removeChannel("test1"));
    EXPECT_EQ(channelFactory.channelExists("test1"), false);
}

TEST(ChannelFactoryClassTests, FindChannel) {
  ChannelFactory channelFactory;

  channelFactory.addNewChannel("channel123");

  std::string existingChannelID = "channel123";
  std::string nonExistingChannelID = "nonexisting";

  // Perform the test actions
  Channel* foundChannel1 = channelFactory.findChannel(existingChannelID);
  Channel* foundChannel2 = channelFactory.findChannel(nonExistingChannelID);

  // Assert 
  EXPECT_NE(nullptr, foundChannel1);
  EXPECT_EQ(nullptr, foundChannel2);
}

