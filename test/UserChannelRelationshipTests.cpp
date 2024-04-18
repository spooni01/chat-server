// is included in ChannelFactoryClass.cpp
// #include "../src/Classes/UserChannelRelationship/UserChannelRelationship.cpp"
 
TEST(UserChannelRelationshipClassTests, CreationOfUserChannelRelationship) { 
	Channel channel("default");
    User user("xlizic00", "adam", "secret123");
    UserChannelRelationship rel(&user, &channel);

	EXPECT_EQ(rel.getUser(), &user);
    EXPECT_EQ(rel.getChannel(), &channel);
}

TEST(UserChannelRelationshipClassTests, SettingNewUserChannelRelationship) {
	Channel channel("default");
    Channel newChannel("new");

    User user("xlizic00", "adam", "secret123");
    UserChannelRelationship rel(&user, &channel);

	EXPECT_EQ(rel.getUser(), &user);
    EXPECT_EQ(rel.getChannel(), &channel);

    EXPECT_NO_THROW(rel.setChannel(&newChannel));
    EXPECT_EQ(rel.getChannel(), &newChannel);
}
