#include "ChangeCommand.h"
#include "GlobalTables.h"
#include "InterpreterEx3.h"
#include <string.h>
#include <iostream>

/**
 * function name: is_num
 * operation: decides if s is a number or not (
 * input: string s
 * @return true if s is a number and false otherwise
 */
bool is_num(string s) {
  for (char c : s) {
    if (isdigit(c) || c == '.' || c == '\0') {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

/**
 * function name: execute
 * operation: find the assign operation
 * input: vector of strings and index
 * @return int value
 */
int ChangeCommand::execute(vector<string> cmdTemp, int index) {

  int newLine = enterKey(cmdTemp, index);
  if (strcmp("=", cmdTemp.at(index + 1).c_str()) == 0) {
    if (is_num(cmdTemp[index + 2])) {
      changeData(cmdTemp.at(index), cmdTemp[index + 2]);
      return newLine;
    }
    InterpreterEx3 *iChange = new InterpreterEx3();
    try {
      //interpreting & calculating cmdTemp[index + 2]
      changeData(cmdTemp.at(index), to_string(iChange->calculateExpression(cmdTemp[index + 2])));
      delete iChange;
    } catch (const char *e) {
      if (iChange != nullptr) {
        delete iChange;
      }
      std::cout << e << std::endl;
      throw e;
    }
  } else {
    printf("Error parser");
  }
  return newLine;
}

/**
 * function name: changeData
 * operation: change data at index
 * input: strings
 * @return int value
 */
void ChangeCommand::changeData(string var, string value) {

  string address = symbolAddr.at(var);
  value = to_string(stod(value.c_str()));
  symbolTable.at(var) = stod(value);

  if (newOrder == "") {
    newOrder = "set " + address + " " + value + "\r\n";
  }
  while (newOrder != "") {}
  newOrder = "set " + address + " " + value + "\r\n";
}

/**
 * function name: enterKey
 * operation: enter a key func
 * input: vec of strings and index
 * @return int value
 */
int ChangeCommand::enterKey(vector<string> vec, int index) {
  int i = 0;
  while (vec.at(index + i) != "\n") {
    i++;
  }
  return i;
}

/**
 * function name: vectorToString
 * operation: convert vec to str
 * input: vec of strings, index, and end index
 * @return string
 */
string ChangeCommand::vectorToString(vector<string> vector, int index, int end) {
  string ret = vector.at(index) + " ";
  int i = 1;
  while (index + i < end) {
    if (ret.length() > 1)
      ret += vector.at(index + i) + " ";
    else {
      break;
    }
    i++;
  }
  return ret;
}

