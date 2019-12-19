//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_MAPS_H
#define CPPEX3_MAPS_H

#include "VarTypes.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Maps {
public:
    static void createAddressTable();
    static void updateFromSimulator(vector<double> params);
    static void addVar(string varName, string bind, string atSimulator);//
    static void addSim(string varName, string atSimulator, string bind);
    static map<string, VarTypes*> symbolTable;
    static map<string, VarTypes*> notInGeneric;
    static map<string,double> addresses;
};


#endif //CPPEX3_MAPS_H
