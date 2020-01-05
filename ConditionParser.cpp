#include "ConditionParser.h"
#include "InterpreterEx3.h"

/**
 * function name: conditionReader
 * operation: read and parse condition
 * input: vec of strings and index
 * @return int
 */
int ConditionParser::conditionReader(vector<string> cmdLines, int index) {
  //should work if the condition has one operator and looks like "a op b", and a,b don't have operators
  int posOp = opCheck(cmdLines, index);
  int endLine = enterKey(cmdLines, index);
  string temp1 = vectorToString(cmdLines, index + 1, posOp - 1);
  string temp2 = vectorToString(cmdLines, index + posOp + 1, endLine - posOp - 2);
  this->a = temp1;
  this->op = cmdLines.at(index + posOp);
  this->b = temp2;
  return endLine;
}

/**
 * function name: check
 * operation: check keys and calculate
 * input: none
 * @return boolean
 */
bool ConditionParser::check() {
  InterpreterEx3 *iCondition = new InterpreterEx3();
  double result = -1;
  string conditionStr = a + op + b;
  try {
    result = iCondition->calculateExpression(conditionStr);
    delete iCondition;
    if (result) {
      return true;
    } else {
      return false;
    }
  } catch (const char *e) {
    if (iCondition != nullptr) {
      delete iCondition;
    }
    throw e;
  }
}

/**
 * function name: execute
 * operation: execute data
 * input: vec of strs and index
 * @return int val
 */
int ConditionParser::execute(vector<string> cmdTemp, int index) {
  //basically this execute is not needed because of other functions so it'll return 0 and will be overridden
  //the use of x and y is for avoiding -Wunused-parameter warnings
  int x = cmdTemp.size() - cmdTemp.size(); // =0
  int y = index - index; //=0
  return x + y; // return 0
}

/**
 * function name: opCheck
 * operation: check keys and calculate
 * input: vec of strs and index
 * @return int val
 */
int ConditionParser::opCheck(vector<string> vector, int index) {
  int i = 0;
  string s = vector.at(index);
  while (s != ">" && s != "<" && s != "<=" && s != ">=" && s != "==" && s != "!=") {
    s = vector.at(index + i);
    i++;
  }
  return i - 1;
}

/**
 * function name: vectorToString
 * operation: convert vector to string
 * input: vec of strs and index
 * @return string val
 */
string ConditionParser::vectorToString(vector<string> vector, int index, int end) {
  string ret = vector.at(index);
  int i = 1;
  while (index + i < index + end) {
    ret += vector.at(index + i);
    i++;
  }
  return ret;
}

/**
 * function name: enterKey
 * operation: enter a key
 * input: vec of strs and index
 * @return int val
 */
int ConditionParser::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i - 2;
}




