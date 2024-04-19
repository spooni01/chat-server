/**
 *  @file   test/ClientSimulator/TPCClientSimulator.cpp
 *  @brief  Class to simulate client chat
 *  @author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 *  @note   To check which port and ip address use, write `ss -ltpn` into terminal.
 *  @note   To start virtual server, write `nc -lkp {port number, f.e. 8088}`
 */

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

class TCPClientSimulator {
public:
    TCPClientSimulator(const std::string& serverAddress, int serverPort) : serverAddress_(serverAddress), serverPort(serverPort) {}

    ~TCPClientSimulator() {
        if (socketDescriptor_ != -1) {
            close(socketDescriptor_);
        }
    }

    /**
     * Sends a TCP packet containing the provided text.
     *
     * @param texttosend The text to be sent in the packet.
     * @return true on successful transmission, false otherwise.
     */
    bool sendmsg(const std::string& texttosend) {
        // Create a socket
        socketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0);
        if (socketDescriptor_ == -1) {
            std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
            return false;
        }

        // Set up server address structure
        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort); // Convert port number to network byte order
        if (inet_pton(AF_INET, serverAddress_.c_str(), &serverAddr.sin_addr) <= 0) {
            std::cerr << "Error converting server address: " << strerror(errno) << std::endl;
            close(socketDescriptor_);
            socketDescriptor_ = -1;
            return false;
        }

        // Connect to the server
        if (connect(socketDescriptor_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Error connecting to server: " << strerror(errno) << std::endl;
            close(socketDescriptor_);
            socketDescriptor_ = -1;
            return false;
        }

        // Prepare the packet data (consider adding packet headers for structure)
        const std::string packetData = texttosend;

        // Send the packet data
        ssize_t bytesSent = send(socketDescriptor_, packetData.c_str(), packetData.length(), 0); // Corrected type for bytesSent
        if (bytesSent == -1) {
            std::cerr << "Error sending data: " << strerror(errno) << std::endl;
            close(socketDescriptor_);
            socketDescriptor_ = -1;
            return false;
        } else if (static_cast<size_t>(bytesSent) != packetData.length()) {
            std::cerr << "Incomplete data sent: " << bytesSent << " bytes out of " << packetData.length() << std::endl;
            close(socketDescriptor_);
            socketDescriptor_ = -1;
            return false;
        }

        // Close the socket (optional, can be left open for multiple sends)
        close(socketDescriptor_);
        socketDescriptor_ = -1;

        return true;
    }

private:
    std::string serverAddress_;
    int socketDescriptor_ = -1; // Track socket descriptor for proper resource management
    int serverPort;
};
