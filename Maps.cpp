//
// Created by sharon on 12/15/19.
//

#include "Maps.h"
#include "VarTypes.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
map<string, double> Maps::addresses;
map<string, VarTypes> Maps::symbolTable;
map<string, string> Maps::binds;
map<string, double> Maps::notXML;

void Maps::createAddressTable() {
    pthread_mutex_lock(&lock);
    addresses.insert(pair<string,double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
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
    addresses.find("/instrumentation/altimeter/indicated-altitude-ft")->second = params.at(1);
    addresses.find("/instrumentation/altimeter/pressure-alt-ft")->second = params.at(2);
    addresses.find("/instrumentation/attitude-indicator/indicated-pitch-deg")->second = params.at(3);
    addresses.find("/instrumentation/attitude-indicator/indicated-roll-deg")->second = params.at(4);
    addresses.find("/instrumentation/attitude-indicator/internal-pitch-deg")->second = params.at(5);
    addresses.find("/instrumentation/attitude-indicator/internal-roll-deg")->second = params.at(6);
    addresses.find("/instrumentation/encoder/indicated-altitude-ft")->second = params.at(7);
    addresses.find("/instrumentation/encoder/pressure-alt-ft")->second = params.at(8);
    addresses.find("/instrumentation/gps/indicated-altitude-ft")->second = params.at(9);
    addresses.find("/instrumentation/gps/indicated-ground-speed-kt")->second = params.at(10);
    addresses.find("/instrumentation/gps/indicated-vertical-speed")->second = params.at(11);
    addresses.find("/instrumentation/heading-indicator/indicated-heading-deg")->second = params.at(12);
    addresses.find("/instrumentation/magnetic-compass/indicated-heading-deg")->second = params.at(13);
    addresses.find("/instrumentation/slip-skid-ball/indicated-slip-skid")->second = params.at(14);
    addresses.find("/instrumentation/turn-indicator/indicated-turn-rate")->second = params.at(15);
    addresses.find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm")->second = params.at(16);
    addresses.find("/controls/flight/aileron")->second = params.at(17);
    addresses.find("/controls/flight/elevator")->second = params.at(18);
    addresses.find("/controls/flight/rudder")->second = params.at(19);
    addresses.find("/controls/flight/flaps")->second = params.at(20);
    addresses.find("/controls/engines/current-engine/throttle")->second = params.at(21);
    addresses.find("/engines/engine/rpm")->second = params.at(22);
    pthread_mutex_unlock(&lock);
}

void Maps::addToAddresses(string address,double val) {
    pthread_mutex_lock(&lock);
    if (addresses.find(address) == addresses.end()) {
        if(notXML.find(address) == notXML.end()) {
            // notXML.insert(pair<string, double>(address, ComunicateWithSimulator::getFromServer(address)));
            notXML.insert(pair<string, double>(address, 0));
        }
        else {
            notXML.find(address)->second = val;
        }
    } else {
        addresses.find(address)->second = val;
    }
    pthread_mutex_unlock(&lock);
}
/**
 *  the method checks if the address is in one of the addresses tables
 */
bool Maps::isAddressExist(string address) {
    pthread_mutex_lock(&lock);
    pthread_mutex_unlock(&lock);
    return (addresses.find(address) != addresses.end() ||
            notXML.find(address)  != notXML.end());
}
/**
 * the method returns the value of the address
 */
double Maps::getValOfAddress (string address) {
    pthread_mutex_lock(&lock);
    if (addresses.find(address) == addresses.end()) {
        if (notXML.find(address) == notXML.end()) {
            cout << "wrong input" << endl;
            pthread_mutex_unlock(&lock);
            return NULL;
        }
        //notXML.find(address)->second = ComunicateWithSimulator::getFromServer(address);
        pthread_mutex_unlock(&lock);
        return notXML.find(address)->second;
    }
    pthread_mutex_unlock(&lock);
    return addresses.find(address)->second;
}
/**
 * the method adds a new var to the symbol table or updates an existing var
 */
void Maps::addVar(string varName,double val) {
    if (symbolTable.find(varName) == symbolTable.end()) {
        symbolTable.insert(pair<string, double> (varName, val));
        varType.insert(pair<string, string>(varName, ));
    } else {
        symbolTable.find(varName)->second = val;
    }
}
/**
 * the method check if a var is in the symbol table
 */
bool Maps::isVarExist(string varName) {
    return (symbolTable.find(varName) != symbolTable.end());
}
/**
 * the method returns the value of the var
 */
double Maps::getVarValue (string varName) {
    pthread_mutex_lock(&lock);
    if (symbolTable.find(varName) == symbolTable.end()) {
        cout << "wrong input" << endl;
        pthread_mutex_unlock(&lock);
        return NULL;
    }
    // if it binds to another var/address
    if (binds.find(varName) != binds.end()) {
        if(addresses.find(binds.find(varName)->second) != addresses.end() ||
           notXML.find(binds.find(varName)->second)  != notXML.end()) {
            pthread_mutex_unlock(&lock);
            return getValOfAddress(binds.find(varName)->second);
        }
        else {
            pthread_mutex_unlock(&lock);
            return Maps::getVarValue(binds.find(varName)->second);
        }
    }
    pthread_mutex_unlock(&lock);
    return symbolTable.find(varName)->second;
}
/**
 * create a bind
 */
void Maps::addBind(string varName,string address) {
    binds.insert(pair<string, string> (varName, address));
}
/**
 * check if the bind exist
 */
bool Maps::isBindExist(string varName) {
    return (binds.find(varName) != binds.end());
}
/**
 * return the address the var binds to
 */
string Maps::getVarAddress (string varName) {
    if (binds.find(varName) == binds.end()) {
        cout << "wrong input" << endl;
        return NULL;
    }
    return binds.find(varName)->second;
}
