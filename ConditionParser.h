//
// Created by sharon on 12/16/19.
//

#ifndef CPPEX3_CONDITIONPARSER_H
#define CPPEX3_CONDITIONPARSER_H

#include <vector>
#include <list>
#include "Command.h"

using namespace std;

class ConditionParser : public Command {
protected:
    vector<Command> commands;
    ConditionParser();
    int execute(list<string> l);
};

#endif //CPPEX3_CONDITIONPARSER_H
