//
// Created by sharon on 12/11/19.
//


#include "Lexer.h"
#include <thread>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <list>

#ifndef CPPEX3_COMMAND_H
#define CPPEX3_COMMAND_H

using namespace std;


class Command {
public:
    Command() {};
    virtual ~Command() {}
    virtual int execute(list<string> params) {};
};

#endif //CPPEX3_COMMAND_H
