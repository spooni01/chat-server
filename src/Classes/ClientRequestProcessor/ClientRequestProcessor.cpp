#include "ClientRequestProcessor.hpp"

ClientRequestProcessor::ClientRequestProcessor(Message *message, UserFactory *users, int currentClientID, UserChannelRelationshipFactory *relationship, ChannelFactory *channels) {


    // AUTH
    if(message->getMessageType() == Message::MessageType::AUTH) {
        if(users->userExists(message->getUsername())) {
            // user exists

            // check if user is him or not
            if(users->findUser(message->getUsername())->getUniqueID() == currentClientID)
                this->messageTCP = "REPLY NOK IS You are already authorized.";
            else
                this->messageTCP = "REPLY NOK IS User already exists.";
        }
        else {
            // user do not exists yet 
            users->addNewUser(message->getUsername(), message->getDisplayName(), message->getSecret(), currentClientID);
            users->findUserByUniqueID(currentClientID)->state.transitionToOpen();
            relationship->addNewRelationship(users->findUser(message->getUsername()), channels->findChannel("default"));
            this->messageTCP = "REPLY OK IS Auth success.";

        }
    }

    // JOIN
    else if(message->getMessageType() == Message::MessageType::JOIN && users->userExistsByUniqueID(currentClientID)) {
        if(relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel()->getChannelID() != message->getChannelID() || users->findUserByUniqueID(currentClientID)->getDisplayname() != message->getDisplayName()) {
            relationship->removeRelationshipByUser(users->findUserByUniqueID(currentClientID));
            
            // If channel do not exists, create it
            if(!channels->channelExists(message->getChannelID()))
                channels->addNewChannel(message->getChannelID());

            // Make new relationship
            relationship->addNewRelationship(users->findUserByUniqueID(currentClientID), channels->findChannel(message->getChannelID()));

            // SendfindChannel
            this->messageTCP = "MSG FROM Server IS ";
            this->messageTCP += users->findUserByUniqueID(currentClientID)->getDisplayname();
            this->messageTCP += " joined ";
            this->messageTCP += relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel()->getChannelID();
            this->messageTCP += ".";
        }
    }

    // MSG
    else if(message->getMessageType() == Message::MessageType::MSG && users->userExistsByUniqueID(currentClientID)) {
        
        // Send
        this->messageTCP = "MSG FROM ";
        this->messageTCP += users->findUserByUniqueID(currentClientID)->getDisplayname();
        this->messageTCP += " IS ";
        this->messageTCP += message->getMessageContent();
    }

    // BYE
    else if(message->getMessageType() == Message::MessageType::BYE && users->userExistsByUniqueID(currentClientID)) {
        this->messageTCP = "";
    }

    else {
        this->messageTCP = "REPLY NOK IS Invalid command sent.";
    }


}


std::string ClientRequestProcessor::getMessageTCP() {

    return this->messageTCP;

}