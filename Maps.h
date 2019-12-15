//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_MAPS_H
#define CPPEX3_MAPS_H

#include "VarTypes.h";
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Maps {
    static map<string,double> addresses;
    static map<string, VarTypes> symbolTable;
    static map<string, string> binds;
    static map<string, double> notXML;
public:
    static void createAddressTable();
    static void updateFromSimulator(vector<double> params);
    static void addToAddresses(string address,double val);//
    static bool isAddressExist(string address);//
    static double getValOfAddress (string address);//
    static void addVar(string varName,double val);//
    static bool isVarExist(string varName);
    static double getVarValue (string varName);
    static void addBind(string varName,string address);
    static bool isBindExist(string varName);
    static string getVarAddress (string varName);
};


#endif //CPPEX3_MAPS_H
