//
// Created by sharon on 12/15/19.
//

#include "simulatorCommunication.h"
#include <vector>
#include "OpenServerCommand.h"
#include "Maps.h"

void openServer(int socket) {
    char buffer[400];
    int n = 0;
    bzero(buffer, 400);
    string line = "";
    string previous = "";
    vector<double> vec;
    while (simulatorCommunication::isCommunicationOpen()) {
        int pos,prev = 0;
        n = read(socket, buffer, 400);
        if (n < 0) {
            perror("Error reading socket");
            exit(1);
        }

        line += string(buffer);
        if (string(buffer) == "exit") {
            break;
        }

        for (int i = 0; i < 22; i++) {
            pos = line.find_first_of(",");
            vec.push_back(stod(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }

        vec.push_back(stod(line.substr(0, line.find_first_of("\n"))));
        line.erase(0, line.find_last_of("\n") + 1);

        Maps::updateFromSimulator(vec);
        vec.clear();
        sleep(1.0);
    }
}

int OpenServerCommand::execute(string l) {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(stod(l));

    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        cerr << "Could not bind socket to IP" << endl;
        exit(1);
    }

    if (listen(sockfd, 5) == -1) {
        cerr << "Error listening" << endl;
        exit(1);
    }
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen);
    cout << "Connected" << endl;

    if (newsockfd == -1) {
        cerr << "Error accepting client" << endl;
        exit(1);
    }

    close(sockfd);

    Maps::createAddressTable();

    char buff;
    int none = recv(newsockfd, &buff, 1, MSG_PEEK);
    thread th(&openServer, stod(l));
    th.join();
    simulatorCommunication::setOpenDataServer(&newsockfd, &th);

    return 2;
}