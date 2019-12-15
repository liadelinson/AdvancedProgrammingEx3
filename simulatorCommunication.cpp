//
// Created by sharon on 12/15/19.
//

#include <unistd.h>
#include "simulatorCommunication.h"
#include "Maps.h"
int simulatorCommunication::sockfd = -1;
int simulatorCommunication::DataServerSocket = -1;
thread* simulatorCommunication::th = 0;
bool simulatorCommunication::isOpen = false;

using namespace std;

bool simulatorCommunication::sendToServer(std::__cxx11::string st, double val) {
    string command = "set" + Maps::getVarAddress(st) + " " + to_string(val) = " \r\n";
    int n = write(sockfd, command.c_str(), command.length());
    if (n < 0) {
        return false;
    }
    return true;
}

double simulatorCommunication::getFromServer(std::__cxx11::string address) {
    string query = "get " + address + " \r\n";
    int n = write(sockfd, query.c_str(), query.length());

    char buffer[200];
    n = read(sockfd, buffer, 200);
    if (n < 0) {
        return 0;
    }

    string result = string(buffer);
    int start = result.find("'");
    result = result.substr(start + 1);
    int end = result.find("'");
    result = result.substr(0, end);
    return stod(result);
}

void simulatorCommunication::closeAll() {
    if (sockfd > 0) {
        close(sockfd);
    }

    if (DataServerSocket > 0) {
        isOpen = false;
        close(DataServerSocket);
    }

    sleep(1);
}