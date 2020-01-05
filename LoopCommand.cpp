#include "LoopCommand.h"
#include "Parser.h"

int LoopCommand::execute(vector<string> cmdTemp, int index) {
  Parser *p = new Parser();
  int endLine = enterKey(cmdTemp, index), ret = 0;
  conditionReader(cmdTemp, index);
  while (check()) {
    ret = p->strPrsTarget(cmdTemp, index + endLine, "}");
  }
  delete p;
  return ret;
}

int LoopCommand::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i;
}

LoopCommand::LoopCommand(string type1) {
  this->type = type1;
}