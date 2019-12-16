//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_SIMULATORCOMMUNICATION_H
#define CPPEX3_SIMULATORCOMMUNICATION_H

#include <string>
#include <thread>

using namespace std;

class simulatorCommunication {
public:
    static int sockfd;
    static int DataServerSocket;
    static thread* th;
    static bool isOpen;

    static void setSocket(int num) {
        sockfd = num;
    }

    static void setOpenDataServer(int* socket, thread* thr) {
        DataServerSocket = *socket;
        th = thr;
        isOpen = true;
    }

    static bool isCommunicationOpen() {
        return isOpen;
    }

    static bool sendToServer(string st, double val);
    static double getFromServer(string address);
    static void closeAll();
};


#endif //CPPEX3_SIMULATORCOMMUNICATION_H
