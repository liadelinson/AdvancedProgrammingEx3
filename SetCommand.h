//
// Created by sharon on 12/18/19.
//

#ifndef CPPEX3_SETCOMMAND_H
#define CPPEX3_SETCOMMAND_H

#include "Command.h"
#include <list>

class SetCommand : public Command {
public:
    int execute(list<string> l);
};


#endif //CPPEX3_SETCOMMAND_H
