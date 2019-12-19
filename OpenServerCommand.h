//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_OPENSERVERCOMMAND_H
#define CPPEX3_OPENSERVERCOMMAND_H

#include "Command.h"
#include <list>

class OpenServerCommand : public Command {
    ~OpenServerCommand() {};
    int execute(list<string> l);
};


#endif //CPPEX3_OPENSERVERCOMMAND_H
