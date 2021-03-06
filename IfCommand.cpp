#include "IfCommand.h"
#include "Parser.h"

int IfCommand::execute(vector<string> cmdTemp, int index) {
  Parser *p = new Parser();
  int endLine = enterKey(cmdTemp, index), ret = 0;
  conditionReader(cmdTemp, index);
  if (check()) {
    ret = p->strPrsTarget(cmdTemp, index + endLine, "}");
  }
  return ret;
}

int IfCommand::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i;
}