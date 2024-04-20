#include "../../src/Classes/Message/Message.cpp"
 
TEST(MessageClassTests, InvalidMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("Invalid"));
}

TEST(MessageClassTests, AuthMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("AUTH xlizic00 AS adam USE secret123"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::AUTH);
    EXPECT_EQ(msg.getUsername(), "xlizic00");
    EXPECT_EQ(msg.getDisplayName(), "adam");
    EXPECT_EQ(msg.getSecret(), "secret123");
}
 
TEST(MessageClassTests, ErrMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("ERR FROM displayName IS msgContent"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::ERR);
    EXPECT_EQ(msg.getDisplayName(), "displayName");
    EXPECT_EQ(msg.getMessageContent(), "msgContent");
}

 
TEST(MessageClassTests, ReplyMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("REPLY OK IS msgContent"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::REPLY);
    EXPECT_EQ(msg.getMessageContent(), "msgContent");
    EXPECT_EQ(msg.getReplyOKNOK(), "OK");

    EXPECT_NO_THROW(msg.parseTCP("REPLY NOK IS msgContent"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::REPLY);
    EXPECT_EQ(msg.getMessageContent(), "msgContent");
    EXPECT_EQ(msg.getReplyOKNOK(), "NOK");
}

 
TEST(MessageClassTests, JoinMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("JOIN channelID AS displayName"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::JOIN);
    EXPECT_EQ(msg.getChannelID(), "channelID");
    EXPECT_EQ(msg.getDisplayName(), "displayName");
}

 
TEST(MessageClassTests, MsgMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("MSG FROM displayName IS msgContent"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::MSG);
    EXPECT_EQ(msg.getDisplayName(), "displayName");
    EXPECT_EQ(msg.getMessageContent(), "msgContent");
}

 
TEST(MessageClassTests, ByeMessage) { 
	Message msg;

    EXPECT_NO_THROW(msg.parseTCP("BYE"));
	EXPECT_EQ(msg.getMessageType(), Message::MessageType::BYE);
}