//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_OPENSERVERCOMMAND_H
#define CPPEX3_OPENSERVERCOMMAND_H

#include "Command.h"

class OpenServerCommand : public Command {
    ~OpenServerCommand() {};
    int execute(string l);
};


#endif //CPPEX3_OPENSERVERCOMMAND_H
