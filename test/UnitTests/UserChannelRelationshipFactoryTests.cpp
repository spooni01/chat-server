#include "../../src/Classes/UserChannelRelationshipFactory/UserChannelRelationshipFactory.cpp"

TEST(UserChannelRelationshipFactoryClassTests, AddedNewRelationship) { 
	Channel channel1("default");
  User user1("xlizic00", "adam", "secret123");
  Channel channel2("general");
  User user2("xlogin00", "fitak", "12456789");
  UserChannelRelationshipFactory relationshipFactory;

	EXPECT_NO_THROW(relationshipFactory.addNewRelationship(&user1, &channel1));
	EXPECT_NO_THROW(relationshipFactory.addNewRelationship(&user2, &channel2));

    EXPECT_EQ(relationshipFactory.relationshipExists(&user1, &channel1), true);
    EXPECT_EQ(relationshipFactory.relationshipExists(&user2, &channel2), true);
    EXPECT_EQ(relationshipFactory.relationshipExists(&user1, &channel2), false);
    EXPECT_EQ(relationshipFactory.relationshipExists(&user2, &channel1), false);

}

TEST(UserChannelRelationshipFactoryClassTests, RemoveRelationshipByUser) {
  Channel channel1("default");
  User user1("xlizic00", "adam", "secret123");
  UserChannelRelationshipFactory relationshipFactory;

  relationshipFactory.addNewRelationship(&user1, &channel1);

  EXPECT_EQ(relationshipFactory.relationshipExists(&user1, &channel1), true);

  relationshipFactory.removeRelationshipByUser(&user1);

  EXPECT_EQ(relationshipFactory.relationshipExists(&user1, &channel1), false);
}

TEST(UserChannelRelationshipFactoryClassTests, FindRelationshipByUser) {
  Channel channel1("default");
  User user1("xlizic00", "adam", "secret123");
  UserChannelRelationshipFactory relationshipFactory;

  relationshipFactory.addNewRelationship(&user1, &channel1);

  UserChannelRelationship* foundRelationship = relationshipFactory.findRelationshipByUser(&user1);

  EXPECT_EQ(foundRelationship->getUser(), &user1);
  EXPECT_EQ(foundRelationship->getChannel(), &channel1);

  User user2("xlogin00", "fitak", "12456789");
  foundRelationship = relationshipFactory.findRelationshipByUser(&user2);
  EXPECT_EQ(foundRelationship, nullptr);
}


