# Chat server using IPK24-CHAT protocol

## Overview
This is a chat server application that facilitates communication between clients using either the User Datagram Protocol (UDP) or Transmission Control Protocol (TCP). It listens for incoming connections and messages from clients, relays messages between connected clients within the same channel, and manages the overall chat experience.

## Usage
```./ipk24chat-server {parameters}```

Parameters:<br>
- **l**: server listening IP address for welcome sockets (predefined value is 0.0.0.0).
- **p**: server listening port for welcome sockets (predefined value is 4567).
- **d**: UDP confirmation timeout (predefined value is 250).
- **r**: maximum number of UDP retransmissions (predefined value is 3).
- **h**: prints program help output and exits.

## Architecture Overview
Work with users, channels and relationships between them is created using the Factory pattern designed for object-oriented programming. The ChannelFactory, UserFactory and UserChannelRelationshipFactory classes contain a list of all current elements and functions for working with users, channels or user-channel relationships.

### Client-Server Communication Flow Diagram
todo

### Class Diagram
todo

## Exceptions
This section describes the exception handling mechanism used in this project. Exceptions are objects thrown by functions to indicate error conditions.

Error codes and what they mean:
- **0**: there is no error in code (zero is not error code but it is there just for documentation purpose).
- **10**: error code for invalid argument provided to a function. (implemented Exceptions/ArgumentException.cpp)
- **20**: error code for invalid channel name. (implemented Exceptions/ChannelException.cpp)
- **30**: error code for user problems. (implemented Exceptions/UserException.cpp)
- **99**: generic error code for unexpected errors.

## Tests
Unit testing is done using Google Test with separate test files for each class, promoting modularity and focused testing.  This approach simplifies maintenance and improves test organization.<br>
In tests there is also class ClientClass that simulates client.<br>
Test can be run using the `make test` command.

## License
This project is licensed under the [GNU General Public License v3.0 (GPL-3.0)](https://www.gnu.org/licenses/gpl-3.0.html). See the [LICENSE](LICENSE) file for details.
