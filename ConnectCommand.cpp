//
// Created by sharon on 12/15/19.
//

#include "simulatorCommunication.h"
#include "ConnectCommand.h"
#include <netinet/in.h>
#include <arpa/inet.h>>
#include <unistd.h>
#include <sys/socket.h>

int ConnectCommand::execute(string l) {
    string ip = l.substr(0, l.find(","));
    l.erase(0, l.find(",") + 1);


    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error creating socket" << endl;
        exit(1);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(stod(l));

    int is_connected = connect(sockfd, (struct sockaddr*) &address, sizeof(address));
    if (is_connected == -1) {
        cerr << "Error connecting to server" << endl;
        exit(1);
    }

    simulatorCommunication::setSocket(sockfd);
    return 3;
}