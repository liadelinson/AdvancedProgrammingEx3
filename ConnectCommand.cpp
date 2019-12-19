//
// Created by sharon on 12/15/19.
//

#include "simulatorCommunication.h"
#include "ConnectCommand.h"
#include <netinet/in.h>
#include <arpa/inet.h>>
#include <list>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;

int ConnectCommand::execute(list<string> l) {

    list<string>::iterator it = l.begin();
    string port = *it;
    ++it;
    string ip = *it;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "Error creating socket" << endl;
        exit(1);
    }

    cout << "ip is " + ip + " and port is " + port << endl;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(stod(port));

    int is_connected = connect(sockfd, (struct sockaddr*) &address, sizeof(address));
    if (is_connected == -1) {
        cerr << "Error connecting to server" << endl;
        exit(1);
    }

    simulatorCommunication::setSocket(sockfd);
    return 3;
}