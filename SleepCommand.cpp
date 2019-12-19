//
// Created by sharon on 12/17/19.
//

#include "SleepCommand.h"

int SleepCommand::execute(list<string> l) {
    sleep(stod(l.front()));
}