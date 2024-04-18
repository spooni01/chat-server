// is included in ChannelFactoryClass.cpp
// #include "../src/Classes/User/User.cpp"
 
TEST(UserClassTest, BasicTest) { 
	User user("xlizic00", "adam", "secret123");

	EXPECT_EQ(user.getUsername(), "xlizic00");
	EXPECT_EQ(user.getDisplayname(), "adam");
}

TEST(UserClassTest, InvalidUsernameLength) {
	std::string invalidUsername = "ThisUsernameIsTooLongggg";
	std::string displayname = "Valid Display";
	std::string secret = "secret123";

	EXPECT_THROW({ User user(invalidUsername, displayname, secret); }, UserException);
}

TEST(UserClassTest, InvalidUsernameCharacters) {
	std::string invalidUsername = "invalid@user";
	std::string displayname = "Valid Display";
	std::string secret = "secret123";

	EXPECT_THROW({ User user(invalidUsername, displayname, secret); }, UserException);
}

TEST(UserClassTest, UsernameValidationFunction) {
	User user("xlizic00", "adam", "secret123");
	std::string validUsername = "validuser123";
	std::string invalidUsername1 = "too_long_username";
	std::string invalidUsername2 = "invalid@user";

	EXPECT_TRUE(user.isUsernameFormatCorrect(validUsername));
	EXPECT_FALSE(user.isUsernameFormatCorrect(invalidUsername1));
	EXPECT_FALSE(user.isUsernameFormatCorrect(invalidUsername2));
}

TEST(UserTest, SecretValidationFunction) {
	User user("xlizic00", "adam", "secret123");
	std::string validSecret = "ThisIsAValidSecret";
	std::string invalidSecret1 = "TooLongSecretHereMoreThan128CharsTooLongSecretHereMoreThan128CharsTooLongSecretHereMoreThan128CharsTooLongSecretHereMoreThan128Chars";
	std::string invalidSecret2 = "invalid$secret";

	EXPECT_TRUE(user.isSecretFormatCorrect(validSecret));
	EXPECT_FALSE(user.isSecretFormatCorrect(invalidSecret1));
	EXPECT_FALSE(user.isSecretFormatCorrect(invalidSecret2));
}

TEST(UserTest, DisplaynameValidationFunction) {
	User user("xlizic00", "adam", "secret123");
	std::string validDisplayname = "ValidDisplayName";
	std::string invalidDisplayname1 = "DisplayNameTooLongHere";
	std::string invalidDisplayname2 = "inval\nid!$";

	EXPECT_TRUE(user.isDisplaynameFormatCorrect(validDisplayname));
	EXPECT_FALSE(user.isDisplaynameFormatCorrect(invalidDisplayname1));
	EXPECT_FALSE(user.isDisplaynameFormatCorrect(invalidDisplayname2));
}


