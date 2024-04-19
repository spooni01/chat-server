#include "../../src/Classes/NetworkHandlers/TCPProtocolHandler/TCPProtocolHandler.cpp"
 
UserFactory users;
TCPProtocolHandler tcp("0.0.0.0", 4567);
TCPClientSimulator client("0.0.0.0", 4567);


void listenThread_1() {
  tcp.listenForSockets(&users, 1);
}
void listenThread_2() {
  tcp.listenForSockets(&users, 2);
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


    EXPECT_EQ(users.getNumberOfUsers(), 1);
}


TEST(TCPProtocolHandlerClassTests, BasicTwoUsersAuth) { 
    users.removeAllUsers();

    // Go to thread
    std::thread listenThreadObj(listenThread_2);

    // Sleep
    std::this_thread::sleep_for(std::chrono::duration<double>(0.01));
    
    // Send client
    client.sendmsg("AUTH xlizic00 AS adam USING secret123");
    client.sendmsg("AUTH xlogin00 AS login USING 123secret");

    // Join
    listenThreadObj.join();


    EXPECT_EQ(users.getNumberOfUsers(), 2);
}

