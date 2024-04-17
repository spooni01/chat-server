# Chat server using IPK24-CHAT protocol

## Overview
This is a chat server application that facilitates communication between clients using either the User Datagram Protocol (UDP) or Transmission Control Protocol (TCP). It listens for incoming connections and messages from clients, relays messages between connected clients within the same channel, and manages the overall chat experience.

## Usage
```./ipk24chat-server {parameters}```

Parameters:<br>
- **todo**: todo
- **Server (-s)**: The address or hostname of the chat server.
- **Port (-p)**: The port number on which the chat server is listening.
- **Timeout (-d)**: Set the timeout value for communication in milliseconds.
- **Retransmissions (-r)**: Set the number of retransmissions for lost packets.

## Architecture Overview
todo

### Client-Server Communication Flow Diagram
todo

## Exceptions
This section describes the exception handling mechanism used in this project. Exceptions are objects thrown by functions to indicate error conditions.

Error codes and what they mean:
- **0**: there is no error in code (0 is not error code but it is there just for documentation purpose).
- **10**: error code for invalid argument provided to a function. (in Exceptions/ArgumentException.cpp)
- **99**: generic error code for unexpected errors.

### Class Diagram
todo

## Tests
todo


## License
This project is licensed under the [GNU General Public License v3.0 (GPL-3.0)](https://www.gnu.org/licenses/gpl-3.0.html). See the [LICENSE](LICENSE) file for details.
