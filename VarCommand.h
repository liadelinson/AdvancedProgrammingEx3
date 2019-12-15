//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_VARCOMMAND_H
#define CPPEX3_VARCOMMAND_H

#include "Command.h"

class VarCommand : public Command {
public:
    ~VarCommand() {};
    int execute(string l);
};


#endif //CPPEX3_VARCOMMAND_H
