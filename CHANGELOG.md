# CHANGELOG
All notable changes to this project will be documented in this file.

## [0.0.1] - 2024-04-20
### JOINing same channel
- If the user is already in the given channel and requests to JOIN again to the given channel with the same displayname, nothing will be done (in UDP communication only a packet of correctness will arrive). If he connects to the same channel but with a different display name, everything will happen as if he had connected to a completely different channel.

## [0.0.1] - 2024-04-17
### Note
- When someone is in specific channel and send JOIN attemp to the same channel in which he is, response from server will be CORRECT but broadcast message to other users ("{DisplayName} join channel {channelID}") in the same channel will be not send