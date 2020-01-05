#include "SleepCommand.h"
#include "InterpreterEx3.h"
#include <thread>

/**
 * function name: execute
 * operation: execute a data
 * input: vector of strs and index
 * @return int
 */
int SleepCommand::execute(vector<string> cmdTemp, int index) {
  InterpreterEx3 *iSleep = new InterpreterEx3();

  int endLine = enterKey(cmdTemp, index);
  string temp = vectorToString(cmdTemp, index + 1, index + endLine);
  try {
    int time = iSleep->calculateExpression(temp);
    this_thread::sleep_for(chrono::milliseconds(time));
    delete iSleep;
  } catch (const char *e) {
    if (iSleep != nullptr) {
      delete iSleep;
    }
    throw e;
  }
  return endLine;
}

/**
 * function name: vectorToString
 * operation: convert a vec to str
 * input: vector of strs and index
 * @return string
 */
string SleepCommand::vectorToString(vector<string> vector, int index, int end) {
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
 * input: vector of strs and index
 * @return int
 */
int SleepCommand::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i;
}