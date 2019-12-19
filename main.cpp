#include <iostream>
#include "Command.h"
#include "Lexer.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "VarCommand.h"
#include "IfCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include <unordered_map>
#include <map>

using namespace std;

void createMap(unordered_map<string, Command*> commandsMap) {
    commandsMap.insert(pair<string, Command*>("openDataServer", new OpenServerCommand()));
    commandsMap.insert(pair<string, Command*>("connectControlClient", new ConnectCommand()));
    commandsMap.insert(pair<string, Command*>("var", new VarCommand()));
    commandsMap.insert(pair<string, Command*>("Print", new PrintCommand()));
    commandsMap.insert(pair<string, Command*>("Sleep", new SleepCommand()));
    commandsMap.insert(pair<string, Command*>("if", new IfCommand()));
}

void createJumpMap(unordered_map<string, int> jumpMap) {
    jumpMap.insert(pair<string, int>("openDataServer", 1));
    jumpMap.insert(pair<string, int>("connectControlClient", 2));
    jumpMap.insert(pair<string, int>("var", 4));
    jumpMap.insert(pair<string, int>("Print", 1));
    jumpMap.insert(pair<string, int>("Sleep", 1));
}

void parser(unordered_map<string, Command*> commands, unordered_map<string, int> jumps, list<string> tokenList) {
    list<string>::iterator it = tokenList.begin();
    list<string> params;

    //cout << "now parsing: " + *it << endl;

    while (it != tokenList.end()) {

        //cout << "now parsing: " + *it << endl;

        list<string>::iterator currentLocation = it;
        ++currentLocation;
        for (int i = 0; i < jumps[*it]; i++) {
            params.insert(params.begin(), *currentLocation);
            ++currentLocation;
        }

        //for (auto it = params.begin(); it != params.end(); it++) {
        //    cout << *it << endl;
        //}

        Command *c = commands[*it];
        advance(it, c->execute(params));
        params.clear();
    }
}

int main(int argc, char* argv[]) {

    unordered_map<string, Command*> commandsMap;
    unordered_map<string, int> jumpMap;

    commandsMap.insert(pair<string, Command*>("openDataServer", new OpenServerCommand()));
    commandsMap.insert(pair<string, Command*>("connectControlClient", new ConnectCommand()));
    commandsMap.insert(pair<string, Command*>("var", new VarCommand()));
    commandsMap.insert(pair<string, Command*>("Print", new PrintCommand()));
    commandsMap.insert(pair<string, Command*>("Sleep", new SleepCommand()));
    commandsMap.insert(pair<string, Command*>("if", new IfCommand()));

    jumpMap.insert(pair<string, int>("openDataServer", 1));
    jumpMap.insert(pair<string, int>("connectControlClient", 2));
    jumpMap.insert(pair<string, int>("var", 4));
    jumpMap.insert(pair<string, int>("Print", 1));
    jumpMap.insert(pair<string, int>("Sleep", 1));

    ifstream f;
    f.open("flying.txt", ios::out);
    Lexer* a = new Lexer;
    a->readFile(f);
    //a->printAll();

    parser(commandsMap, jumpMap, a->finalList);

    return 0;
}
