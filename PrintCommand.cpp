#include "PrintCommand.h"
#include "GlobalTables.h"
#include "InterpreterEx3.h"
#include <iostream>
#include <thread>

/**
 * function name: execute
 * operation: execute a data
 * input: vector of strs and index
 * @return int
 */
int PrintCommand::execute(vector<string> cmdTemp, int index) {
  InterpreterEx3 *iPrint = new InterpreterEx3();
  GlobalTables *gT = new GlobalTables();
  int endLine = enterKey(cmdTemp, index);
  string temp = vectorToString(cmdTemp, index + 1, index + endLine);
  if (temp.find("\"") == string::npos) {
    try {
      this_thread::sleep_for(chrono::milliseconds(30)); //to prevent situation where printing is too quick
      printMeth(to_string(iPrint->calculateExpression(temp)));
      delete iPrint;
    } catch (const char *e) {
      if (iPrint != nullptr) {
        delete iPrint;
      }
      throw e;
    }
  } else {
    printMeth(temp);
  }
  delete gT;
  return endLine;
}

/**
 * function name: printMeth
 * operation: printing message
 * input: string - message
 * @return void
 */
void PrintCommand::printMeth(string message) {
  cout << message << endl;
}

/**
 * function name: vectorToString
 * operation: converting vector of strings (from index to end) to a string
 * input: vector of strs, current index and end index
 * @return string
 */
string PrintCommand::vectorToString(vector<string> vector, int index, int end) {
  string ret = vector.at(index);
  int i = 1;
  while (index + i < end) {
    ret += vector.at(index + i);
  }
  return ret;
}

/**
 * function name: enterKey
 * operation: enter a key
 * input: vector of strs, int index
 * @return int
 */
int PrintCommand::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i;
}