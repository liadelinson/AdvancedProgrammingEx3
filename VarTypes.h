//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_VARTYPES_H
#define CPPEX3_VARTYPES_H

#include <string>

using namespace std;

class VarTypes {
public:
    int _value;
    string _sim;
    string _bindDirection;

    VarTypes(int value, string sim, string bindDirection) {
        this->_sim = sim;
        this->_value = value;
        this->_bindDirection = bindDirection;
    }
};


#endif //CPPEX3_VARTYPES_H
