//
// Created by sharon on 12/18/19.
//

#include "SetCommand.h"
#include "simulatorCommunication.h"
#include "Maps.h"

int SetCommand::execute(list<string> l) {
    list<string>::iterator it = l.begin();
    string name = *it;
    it++;
    string value = *it;
    simulatorCommunication::sendToServer(Maps::symbolTable[name]->_sim, stod(value));
}