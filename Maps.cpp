//
// Created by sharon on 12/15/19.
//

#include "Maps.h"
#include "VarTypes.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
map<string, double> Maps::addresses;
map<string, VarTypes*> Maps::symbolTable;
map<string, VarTypes*> Maps::notInGeneric;

void Maps::createAddressTable() {
    pthread_mutex_lock(&lock);
    addresses.insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    addresses.insert(pair<string, double>("/instrumentation/heading-indicator/offset-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
    addresses.insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    addresses.insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
    addresses.insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    addresses.insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    addresses.insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    addresses.insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    addresses.insert(pair<string, double>("/controls/flight/aileron", 0));
    addresses.insert(pair<string, double>("/controls/flight/elevator", 0));
    addresses.insert(pair<string, double>("/controls/flight/rudder", 0));
    addresses.insert(pair<string, double>("/controls/flight/flaps", 0));
    addresses.insert(pair<string, double>("/controls/engines/current-engine/throttle", 0));
    addresses.insert(pair<string, double>("/engines/engine/rpm", 0));
    pthread_mutex_unlock(&lock);
}

void Maps::updateFromSimulator(vector<double> params) {
    pthread_mutex_lock(&lock);
    addresses.find("/instrumentation/airspeed-indicator/indicated-speed-kt")->second = params.at(0);
    addresses.find("/instrumentation/heading-indicator/offset-deg")->second = params.at(1);
    addresses.find("/instrumentation/altimeter/indicated-altitude-ft")->second = params.at(2);
    addresses.find("/instrumentation/altimeter/pressure-alt-ft")->second = params.at(3);
    addresses.find("/instrumentation/attitude-indicator/indicated-pitch-deg")->second = params.at(4);
    addresses.find("/instrumentation/attitude-indicator/indicated-roll-deg")->second = params.at(5);
    addresses.find("/instrumentation/attitude-indicator/internal-pitch-deg")->second = params.at(6);
    addresses.find("/instrumentation/attitude-indicator/internal-roll-deg")->second = params.at(7);
    addresses.find("/instrumentation/encoder/indicated-altitude-ft")->second = params.at(8);
    addresses.find("/instrumentation/encoder/pressure-alt-ft")->second = params.at(9);
    addresses.find("/instrumentation/gps/indicated-altitude-ft")->second = params.at(10);
    addresses.find("/instrumentation/gps/indicated-ground-speed-kt")->second = params.at(11);
    addresses.find("/instrumentation/gps/indicated-vertical-speed")->second = params.at(12);
    addresses.find("/instrumentation/heading-indicator/indicated-heading-deg")->second = params.at(13);
    addresses.find("/instrumentation/magnetic-compass/indicated-heading-deg")->second = params.at(14);
    addresses.find("/instrumentation/slip-skid-ball/indicated-slip-skid")->second = params.at(15);
    addresses.find("/instrumentation/turn-indicator/indicated-turn-rate")->second = params.at(16);
    addresses.find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm")->second = params.at(17);
    addresses.find("/controls/flight/aileron")->second = params.at(18);
    addresses.find("/controls/flight/elevator")->second = params.at(19);
    addresses.find("/controls/flight/rudder")->second = params.at(20);
    addresses.find("/controls/flight/flaps")->second = params.at(21);
    addresses.find("/controls/engines/current-engine/throttle")->second = params.at(22);
    addresses.find("/engines/engine/rpm")->second = params.at(23);

    for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        if ((*(it)->second)._direction == "<-") {
            double val = addresses.find((*it->second)._sim)->second;
            (*it->second).updateValue(val);
        }
    }
    pthread_mutex_unlock(&lock);
}

void Maps::addSim (string varName, string atSimulator, string bind) {
    pthread_mutex_lock(&lock);
    if (addresses.find(atSimulator) == addresses.end()) {
        if (notInGeneric.find(atSimulator) == notInGeneric.end()) {
            notInGeneric.insert(pair<string, VarTypes*>(varName, new VarTypes(atSimulator, bind)));
        }
    }
    pthread_mutex_lock(&lock);
}

/**
 * the method adds a new var to the symbol table or updates an existing var
 */
void Maps::addVar(string varName, string bind, string atSimulator) {
    if (symbolTable.find(varName) == symbolTable.end()) {
        symbolTable.insert(pair<string, VarTypes*>(varName, new VarTypes(atSimulator, bind)));
    } else {
        cout << "already in" << endl;
    }
}