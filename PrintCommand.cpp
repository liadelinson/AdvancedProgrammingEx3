//
// Created by sharon on 12/17/19.
//

#include "PrintCommand.h"

int PrintCommand::execute(list<string> l) {
    l.front() = l.front().substr(1, l.front().size() - 2);
    cout << l.front() << endl;

    return 2;
}