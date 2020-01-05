#ifndef OPENSERVERCOMMAND_H
#define OPENSERVERCOMMAND_H

#include "Command.h"

class OpenServerCommand: public Command {
public:
    // pure virtual function
    virtual int execute(vector<string> cmdTemp, int index);
    void openSocket(int port);
    static void *runServer(void *args);
    static vector<double> buffToDouble(string buffer);
    static void updateTable(vector<double> temp);
    int enterKey(vector<string> vec, int index);
    string vectorToString(vector<string> vector, int index, int end);
    ~OpenServerCommand() override = default;
};


#endif //OPENSERVERCOMMAND_H
