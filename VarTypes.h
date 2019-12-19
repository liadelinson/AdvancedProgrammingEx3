//
// Created by sharon on 12/15/19.
//

#ifndef CPPEX3_VARTYPES_H
#define CPPEX3_VARTYPES_H

#include <string>

using namespace std;

class VarTypes {
public:
    double _value = 0;
    string _sim;
    string _direction;

    VarTypes(string sim, string direction) {
        this->_sim = sim;
        this->_direction = direction;
    }

    void updateValue(int value) {
        this->_value = value;
    }
};


#endif //CPPEX3_VARTYPES_H
