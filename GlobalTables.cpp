#include "GlobalTables.h"

vector<string> tableOrder;
map<string, double> symbolTable; // var / value -> from user
map<string, double> symbolServer;  // address  / value -> from simulator
map<string, string> symbolAddr;  // var / address -> from user
map<string, double> symbolReverse; // address / value -> from user
map<string, string> simToVar;
pthread_mutex_t connectLock;
string newOrder;
bool endSignal = false;
bool runClient = false;

/**
 * function name: keyExists
 * operation: check if symbolTable got seek as a key
 * input: string seek
 * @return bool - true if seek is in symbolTable and false otherwise
 */
bool GlobalTables::keyExists(string seek) {
  if (symbolTable.count(seek)) {
    return true;
  } else
    return false;
}

/**
 * function name: revExists
 * operation: check if symbolAddr got seek as a key
 * input: string seek
 * @return bool - true if seek is in symbolAddr and false otherwise
 */
bool GlobalTables::revExists(string seek) {
  if (symbolAddr.count(seek)) {
    return true;
  } else
    return false;
}

/**
 * function name: GlobalTables
 * operation: constructor of GlobalTables
 */
GlobalTables::GlobalTables() {
  tableOrder.push_back(string("/instrumentation/airspeed-indicator/indicated-speed-kt"));
  tableOrder.push_back(string("/sim/time/warp"));
  tableOrder.push_back(string("/controls/switches/magnetos"));
  tableOrder.push_back(string("/instrumentation/heading-indicator/offset-deg"));
  tableOrder.push_back(string("/instrumentation/altimeter/indicated-altitude-ft"));
  tableOrder.push_back(string("/instrumentation/altimeter/pressure-alt-ft"));
  tableOrder.push_back(string("/instrumentation/attitude-indicator/indicated-pitch-deg"));
  tableOrder.push_back(string("/instrumentation/attitude-indicator/indicated-roll-deg"));
  tableOrder.push_back(string("/instrumentation/attitude-indicator/internal-pitch-deg"));
  tableOrder.push_back(string("/instrumentation/attitude-indicator/internal-roll-deg"));
  tableOrder.push_back(string("/instrumentation/encoder/indicated-altitude-ft"));
  tableOrder.push_back(string("/instrumentation/encoder/pressure-alt-ft"));
  tableOrder.push_back(string("/instrumentation/gps/indicated-altitude-ft"));
  tableOrder.push_back(string("/instrumentation/gps/indicated-ground-speed-kt"));
  tableOrder.push_back(string("/instrumentation/gps/indicated-vertical-speed"));
  tableOrder.push_back(string("/instrumentation/heading-indicator/indicated-heading-deg"));
  tableOrder.push_back(string("/instrumentation/magnetic-compass/indicated-heading-deg"));
  tableOrder.push_back(string("/instrumentation/slip-skid-ball/indicated-slip-skid"));
  tableOrder.push_back(string("/instrumentation/turn-indicator/indicated-turn-rate"));
  tableOrder.push_back(string("/instrumentation/vertical-speed-indicator/indicated-speed-fpm"));
  tableOrder.push_back(string("/controls/flight/aileron"));
  tableOrder.push_back(string("/controls/flight/elevator"));
  tableOrder.push_back(string("/controls/flight/rudder"));
  tableOrder.push_back(string("/controls/flight/flaps"));
  tableOrder.push_back(string("/controls/engines/engine/throttle"));
  tableOrder.push_back(string("/controls/engines/current-engine/throttle"));
  tableOrder.push_back(string("/controls/switches/master-avionics"));
  tableOrder.push_back(string("/controls/switches/starter"));
  tableOrder.push_back(string("/engines/active-engine/auto-start"));
  tableOrder.push_back(string("/controls/flight/speedbrake"));
  tableOrder.push_back(string("/sim/model/c172p/brake-parking"));
  tableOrder.push_back(string("/controls/engines/engine/primer"));
  tableOrder.push_back(string("/controls/engines/current-engine/mixture"));
  tableOrder.push_back(string("/controls/switches/master-bat"));
  tableOrder.push_back(string("/controls/switches/master-alt"));
  tableOrder.push_back(string("/engines/engine/rpm"));

  for (int i = 0; i < (int) (tableOrder.size()); i++) {
    symbolServer[tableOrder.at(i)] = 0;
  }
}

/**
 * function name: getVal
 * operation: get value of key from symbolTable, if possible
 * input: string key
 * @return double value
 */
double GlobalTables::getVal(string key) {
  double value;
  try {
    value = symbolTable.find(key)->second;
  }
  catch (exception &e) {
    throw runtime_error("error, the key is not found");
  }
  return value;
}

/**
 * function name: getValues
 * operation: returns key & values from maps
 * @return string ret
 */
string GlobalTables::getValues() {
  pthread_mutex_lock(&connectLock);
  string ret = "";
  for (int i = 0; i < (int) (tableOrder.size()); i++) {
    try {
      if (revExists(tableOrder.at(i))) {
        ret += to_string(symbolReverse.at(tableOrder.at(i)));
      } else {
        ret += to_string(symbolServer.at(tableOrder.at(i))).substr(0, 8);
      }
      if (i + 1 < (int) (tableOrder.size()))
        ret += ",";
    }
    catch (exception &e) {
      printf("Adress not registered\n");
      ret += "0.000000";
      if (i + 1 < (int) (tableOrder.size()))
        ret += ",";
    }
  }
  pthread_mutex_unlock(&connectLock);
  return ret;
}

/**
 * function name: retKeys
 * operation: returns keys from symbolTable
 * @return vector of strings v of keys
 */
vector<string> GlobalTables::retKeys() {
  vector<string> v;
  for (map<string, double>::iterator it = symbolTable.begin(); it != symbolTable.end(); ++it) {
    v.push_back(it->first);
  }
  return v;
}

