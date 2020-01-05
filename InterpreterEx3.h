#ifndef INTERPRETEREX3_H
#define INTERPRETEREX3_H

#include "string"

using namespace std;

class InterpreterEx3 {
 private:
  string setVariables(string str2);

 public:
  double calculateExpression(string str1);
};

#endif //INTERPRETEREX3_H