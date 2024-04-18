#include "../../src/Classes/UserFactory/UserFactory.cpp"
 
TEST(UserFactoryClassTests, AddedNewUser) { 
	UserFactory userFactory;

	EXPECT_NO_THROW(userFactory.addNewUser("xlizic00", "adam", "secret"));

    EXPECT_EQ(userFactory.userExists("xlizic00"), true);
}

TEST(UserFactoryClassTests, GettingData) { 
	UserFactory userFactory;

	EXPECT_NO_THROW(userFactory.addNewUser("xlizic00", "adam", "secret"));

    EXPECT_EQ(userFactory.findUser("xlizic00")->getDisplayname(), "adam");
    EXPECT_EQ(userFactory.findUser("xlizic00")->getUsername(), "xlizic00");
}

TEST(UserFactoryClassTests, RemoveUser) {
	UserFactory userFactory;

	EXPECT_NO_THROW(userFactory.addNewUser("xlizic00", "adam", "secret"));
    EXPECT_EQ(userFactory.userExists("xlizic00"), true);

    EXPECT_NO_THROW(userFactory.removeUser("xlizic00"));
    EXPECT_EQ(userFactory.userExists("xlizic00"), false);
}

TEST(UserFactoryClassTests, FindUser) {
  UserFactory userFactory;

  userFactory.addNewUser("xlizic00", "adam", "secret");

  std::string existingUserID = "xlizic00";
  std::string nonExistingUserID = "nonexisting";

  // Perform the test actions
  User* foundUser1 = userFactory.findUser(existingUserID);
  User* foundUser2 = userFactory.findUser(nonExistingUserID);

  // Assert 
  EXPECT_NE(nullptr, foundUser1);
  EXPECT_EQ(nullptr, foundUser2);
}

