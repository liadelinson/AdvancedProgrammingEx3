//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_CONNECTCOMMAND_H
#define CPPEX3_CONNECTCOMMAND_H

#include <vector>
#include "Command.h"

class ConnectCommand : public Command {
public:
    ~ConnectCommand() {};
    int execute(list<string> l);
};


#endif //CPPEX3_CONNECTCOMMAND_H
