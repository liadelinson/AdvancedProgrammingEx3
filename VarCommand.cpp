//
// Created by sharon on 12/15/19.
//

#include "VarCommand.h"
#include "Maps.h"

int VarCommand::execute(list<string> l) {
    list<string>::iterator it = l.begin();
    string atSimulator = *it;
    ++it;
    ++it;
    string bind = *it;
    ++it;
    string varName = *it;

    //cout << varName << endl;

    Maps::addVar(varName, bind, atSimulator);
    Maps::addSim(varName, atSimulator, bind);

    return 5;
}
