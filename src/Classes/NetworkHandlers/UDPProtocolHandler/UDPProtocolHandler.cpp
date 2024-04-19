#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

class UDPReceiver {
public:
  UDPReceiver(const std::string& serverAddress, int serverDefaultPort) : serverAddress_(serverAddress), serverDefaultPort(serverDefaultPort) {}

  ~UDPReceiver() {
    if (socketDescriptor_ != -1) {
      close(socketDescriptor_);
    }
  }

  /**
   * Listens for incoming UDP packets on a specified port and writes them to stdout.
   *
   * @return true on successful setup and reception of at least one packet, false otherwise.
   */
  bool listenAndPrint() {
    // Create a UDP socket
    socketDescriptor_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor_ == -1) {
      std::cerr << "Error creating socket: " << strerror(errno) << std::endl;
      return false;
    }

    // Set up server address structure
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->serverDefaultPort);
    if (inet_pton(AF_INET, serverAddress_.c_str(), &serverAddr.sin_addr) <= 0) {
      std::cerr << "Error converting server address: " << strerror(errno) << std::endl;
      close(socketDescriptor_);
      socketDescriptor_ = -1;
      return false;
    }

    // Bind the socket to the address
    if (bind(socketDescriptor_, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
      std::cerr << "Error binding socket: " << strerror(errno) << std::endl;
      close(socketDescriptor_);
      socketDescriptor_ = -1;
      return false;
    }

    // Prepare poll structure
    struct pollfd pfd;
    pfd.fd = socketDescriptor_;
    pfd.events = POLLIN; // Interested in readability (incoming data)

    while (true) {
      // Wait for incoming data with poll
      int pollResult = poll(&pfd, 1, -1); // Wait indefinitely
      if (pollResult == -1) {
        std::cerr << "Error in poll: " << strerror(errno) << std::endl;
        break;
      } else if (pollResult == 0) {
        // Timeout (unlikely with -1 in timeout)
        continue;
      }

      // Check for readable socket (incoming UDP packet)
      if (pfd.revents & POLLIN) {
        // Receive data from the client
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));
        socklen_t senderAddrSize = sizeof(struct sockaddr_storage);
        struct sockaddr_storage senderAddr;
        ssize_t bytesReceived = recvfrom(socketDescriptor_, buffer, sizeof(buffer), 0,
                                          (struct sockaddr*)&senderAddr, &senderAddrSize);
        if (bytesReceived == -1) {
          std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
          continue;
        }

        // Write received data to stdout
        write(STDOUT_FILENO, buffer, bytesReceived);
      }
    }

    // Close the socket (important on program termination)
    close(socketDescriptor_);
    return true;
  }

private:
  std::string serverAddress_;
  int socketDescriptor_ = -1;
  int serverDefaultPort;
};
