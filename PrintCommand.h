//
// Created by sharon on 12/17/19.
//

#ifndef CPPEX3_PRINTCOMMAND_H
#define CPPEX3_PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command {
    int execute(list<string> l);
};


#endif //CPPEX3_PRINTCOMMAND_H
