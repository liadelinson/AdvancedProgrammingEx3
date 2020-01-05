#include "VarCommand.h"
#include "GlobalTables.h"
#include "InterpreterEx3.h"
#include <string.h>

/**
 * function name: execute
 * operation: execute a data
 * input: vector of strs commands, int index
 * @return int
 */
int VarCommand::execute(vector<string> cmdTemp, int index) {

  if (cmdTemp[index + 2] == "<-") {
    bind(cmdTemp.at(index + 1), cmdTemp.at(index + 3));
    return 4;
  } else if (cmdTemp[index + 2] == "->") {
    toSim(cmdTemp.at(index + 1), cmdTemp.at(index + 3));
    return 4;
  } else if (strcmp("=", cmdTemp.at(index + 2).c_str()) == 0) {
    bindSet(cmdTemp.at(index + 1), cmdTemp.at(index + 3));
    return 4;
  }
  return 0;
}

/**
 * function name: bind
 * operation: binding to that way: "<-"
 * input: string var and string location
 * @return void
 */
void VarCommand::bind(string var, string location) {
  string newLoc = location.substr(1, location.length() - 2);
  double newVar = symbolServer.at(newLoc);
  symbolTable.insert(pair<string, double>(var, newVar));
  symbolAddr.insert(pair<string, string>(var, newLoc));
  symbolReverse.insert(pair<string, double>(newLoc, newVar));
  simToVar.insert(pair<string, string>(newLoc, var));
}

/**
 * function name: toSim
 * operation: binding to that way: "->"
 * input: string var and string location
 * @return void
 */
void VarCommand::toSim(string var, string location) {
  string newLoc = location.substr(1, location.length() - 2);
  double newVar = symbolServer.at(newLoc);
  symbolTable.insert(pair<string, double>(var, newVar));
  symbolAddr.insert(pair<string, string>(var, newLoc));
  symbolReverse.insert(pair<string, double>(newLoc, newVar));
}

/**
 * function name: bindSet
 * operation: setting var = key
 * input: string var and string location
 * @return void
 */
void VarCommand::bindSet(string var, string key) {
  InterpreterEx3 *iVar = new InterpreterEx3();
  GlobalTables *gT = new GlobalTables();
  double tempKey = 0;
  try {
    tempKey = iVar->calculateExpression(key);
    symbolTable.insert(pair<string, double>(var, tempKey));
    symbolAddr.insert(pair<string, string>(var, key));
    symbolReverse.insert(pair<string, double>(key, tempKey));
    delete gT;
    delete iVar;
  } catch (const char *e) {
    if (iVar != nullptr) {
      delete iVar;
    }
    throw e;
  }
}

/**
 * function name: enterKey
 * operation: enter a key
 * input: vector of strs commands, int and str
 * @return int
 */
int VarCommand::enterKey(vector<string> vector, int index) {
  int i = 0;
  while (vector.at(index + i) != "\n") {
    i++;
  }
  return i;
}

/**
 * function name: vectorToString
 * operation: converting vector of strings (from index to end) to a string
 * input: vector of strs, current index and end index
 * @return string
 */
string VarCommand::vectorToString(vector<string> vector, int index, int end) {
  string ret = vector.at(index);
  int i = 1;
  while (i < end) {
    ret += vector.at(index + i);
  }
  return ret;
}