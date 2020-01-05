#ifndef GLOBALTABLES_H
#define GLOBALTABLES_H

#include <map>
#include <string>
#include <vector>

using namespace std;

extern map<string, double> symbolTable;
extern map<string, double> symbolServer;
extern map<string, string> symbolAddr;
extern map<string, double> symbolReverse;
extern map<string, string> simToVar;
extern vector<string> tableOrder;
extern string newOrder;
extern bool endSignal;
extern bool runClient;
extern pthread_mutex_t connectLock;

class GlobalTables {
 public:
  GlobalTables();
  static vector<string> retKeys();
  double getVal(string val);
  string getValues();
  bool keyExists(string seek);
  bool revExists(string seek);
};

#endif //GLOBALTABLES_H