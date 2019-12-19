//
// Created by sharon on 12/15/19.
//

#include "simulatorCommunication.h"
#include <vector>
#include <list>
#include "OpenServerCommand.h"
#include "Maps.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

void openServer(int socket) {
    char buffer[1024];
    string line = "";
    vector<double> values;

    while (simulatorCommunication::isCommunicationOpen()) {
        int readvalue = read(socket, buffer, 1024);
        int pos = 0;

        if (readvalue == -1) {
            cerr << "Error reading from simulator" << endl;
            exit(1);
        }

        line += buffer;
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        for (int i = 0; i < 22; i++) {
            pos = line.find_first_of(",");
            values.push_back(stod(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }

        values.push_back(stod(line.substr(0, line.find_first_of("\n"))));
        line.erase(0, line.find_first_of("\n") + 1);

        //for (auto it = values.begin(); it != values.end(); ++it) {
        //    cout << *it << endl;
        //}

        Maps::updateFromSimulator(values);
        values.clear();
        sleep(1.0);
    }
}

int OpenServerCommand::execute(list<string> l) {

    string port = l.front();

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5400);

    if (bind(sockfd, (struct sockaddr*) &address, sizeof(address)) == -1) {
        cerr << "Could not bind socket to IP" << endl;
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        cerr << "Error listening" << endl;
        exit(1);
    }

    int client_socket = accept(sockfd, (struct sockaddr*) &address, (socklen_t*) &address);
    cout << "Connected" << endl;

    if (client_socket == -1) {
        cerr << "Error accepting client" << endl;
        exit(1);
    }

    close(sockfd);

    char buff;
    int none = recv(client_socket, &buff, 1, MSG_PEEK);
    thread th(openServer, client_socket);
    th.detach();
    simulatorCommunication::setOpenDataServer(&client_socket, &th);

    return 2;
}