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
            relationship->addNewRelationship(users->findUserByUniqueID(currentClientID), channels->findChannel("default"));
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

            // Send
            this->messageTCP = "MSG FROM Server IS ";
            this->messageTCP += users->findUserByUniqueID(currentClientID)->getDisplayname();
            this->messageTCP += " joined ";
            this->messageTCP += relationship->findRelationshipByUser(users->findUserByUniqueID(currentClientID))->getChannel()->getChannelID();
        }
    }

    // BYE
    else if(message->getMessageType() == Message::MessageType::BYE && users->userExistsByUniqueID(currentClientID)) {
        User *client = users->findUserByUniqueID(currentClientID);
        relationship->removeRelationshipByUser(users->findUserByUniqueID(currentClientID));
        users->removeUser(client->getUsername()); 
        this->messageTCP = "BYE.";
    }

    else {
        this->messageTCP = "REPLY NOK IS First you must log into account.";
    }


}


std::string ClientRequestProcessor::getMessageTCP() {

    return this->messageTCP;

}