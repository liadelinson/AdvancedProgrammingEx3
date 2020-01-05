#ifndef PARSER_H
#define PARSER_H

#include "Command.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Parser {
 public:
  Parser();
  ~Parser();
  void strPrs(vector<string> vecStr);
  int strPrsTarget(vector<string> vecStr, int start, string stop);

 private:
  map<string, Command *> mapCmd;
};

#endif //PARSER_H
