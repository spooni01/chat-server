#include "../../src/Classes/Message/Message.hpp"
#include "../../src/Classes/ClientRequestProcessor/ClientRequestProcessor.cpp"
#include "../../src/Classes/NetworkHandlers/TCPProtocolHandler/TCPProtocolHandler.cpp"

UserFactory users;
TCPProtocolHandler tcp("0.0.0.0", 4567);
TCPClientSimulator client("0.0.0.0", 4567);
TCPClientSimulator client2("0.0.0.0", 4567);
TCPClientSimulator client3("0.0.0.0", 4567);


void listenThread_1() {
  tcp.listenForSockets(&users, 1);
}
TEST(TCPProtocolHandlerClassTests, BasicOneUserAuth) { 
    users.removeAllUsers();

    // Go to thread
    std::thread listenThreadObj(listenThread_1);

    // Sleep
    std::this_thread::sleep_for(std::chrono::duration<double>(0.01));
    
    // Send client
    client.sendmsg("AUTH xlizic00 AS adam USING secret123");

    // Join
    listenThreadObj.join();


    //client.receivePacket();
    //std::cout << client.getReceivedData() << std::endl;


    EXPECT_EQ(users.getNumberOfUsers(), 1);

    // End connection
    //client.sendmsg("BYE");
    //EXPECT_EQ(users.getNumberOfUsers(), 0);

    ///client.closeConnection();
}


void listenThread_2() {
  tcp.listenForSockets(&users, 3);
}
TEST(TCPProtocolHandlerClassTests, AuthorizationToServerFromMoreClients) { 
    users.removeAllUsers();

    // Go to thread
    std::thread listenThreadObj(listenThread_2);

    // Sleep
    std::this_thread::sleep_for(std::chrono::duration<double>(0.01));
    
    // Send client
    client.sendmsg("AUTH xlizic00 AS adam USING secret123");
    client2.sendmsg("AUTH xlogin00 AS login USING 123secret");
    client3.sendmsg("AUTH xyz AS xyz USING xyz");

    // Join
    listenThreadObj.join();


    EXPECT_EQ(users.getNumberOfUsers(), 3);

    // End connection
    //client.sendmsg("BYE");
    //EXPECT_EQ(users.getNumberOfUsers(), 2);
    //client2.sendmsg("BYE");
    //EXPECT_EQ(users.getNumberOfUsers(), 1);
    //client3.sendmsg("BYE");
    //EXPECT_EQ(users.getNumberOfUsers(), 0);
}
