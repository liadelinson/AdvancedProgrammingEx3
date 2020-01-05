#include "Parser.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "VarCommand.h"
#include "LoopCommand.h"
#include "IfCommand.h"
#include "ChangeCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "GlobalTables.h"

/**
 * function name: strPrs
 * operation: parsing commmands from vector
 * input: vector of strs - commands
 * @return void
 */
void Parser::strPrs(vector<string> cmdLines) {
  vector<string> cmdTemp;
  map<string, Command *> mapTmp;
  mapTmp = this->mapCmd;
  string temp;
  Command *c;
  GlobalTables *g = new GlobalTables();
  for (int i = 0; i < (int) (cmdLines.size()); i++) {
    string tmp((cmdLines.at(i)).c_str());
    try {
      if (g->keyExists(tmp)) {
        c = mapTmp["change"];
        i += c->execute(cmdLines, i);
      } else if (cmdLines.at(i) != "\n" && cmdLines.at(i) != "}") {
        c = mapTmp[cmdLines.at(i)];
        i += c->execute(cmdLines, i);
      }
    }
    catch (const char *e) {
      //in case of an error, the run will be ended here
      delete g;
      endSignal = true;
    }
  }
  delete g;
  endSignal = true;
}

/**
 * function name: strPrsTarget
 * operation: similar to strPrs but it parses part of the commands from cmdLines
 * input: vector of strs, int - start - where to start parsing, string - stop - when to stop parsing
 * @return int
 */
int Parser::strPrsTarget(vector<string> cmdLines, int start, string stop) {
  vector<string> cmdTemp;
  map<string, Command *> mapTmp;
  mapTmp = this->mapCmd;
  string temp;
  Command *c;
  int i = 0;
  GlobalTables *g = new GlobalTables();
  for (i = start + 1; cmdLines.at(i) != stop; i++) {
    try {
      string tmp((cmdLines.at(i)).c_str());
      if (g->keyExists(tmp)) {
        c = mapTmp["change"];
        i += c->execute(cmdLines, i);
      } else if (cmdLines.at(i) != "\n") {
        c = mapTmp[cmdLines.at(i)];
        i += c->execute(cmdLines, i);
      }
    }
    catch (const char *e) {
      //in case of an error, the run will be ended here
      delete g;
      endSignal = true;
    }
  }
  delete g;
  return i - start;
}

/**
 * function name: Parser
 * operation: constructor of Parser
 */
Parser::Parser() {
  this->mapCmd[string("openDataServer")] = new OpenServerCommand();
  this->mapCmd[string("while")] = new LoopCommand("while");
  this->mapCmd[string("connectControlClient")] = new ConnectCommand();
  this->mapCmd[string("var")] = new VarCommand();
  this->mapCmd[string("Print")] = new PrintCommand();
  this->mapCmd[string("change")] = new ChangeCommand();
  this->mapCmd[string("Sleep")] = new SleepCommand();
  this->mapCmd[string("if")] = new IfCommand();
}

/**
 * function name: ~Parser
 * operation: destructor of Parser
 */
Parser::~Parser() {
  for (map<string, Command *>::iterator it = mapCmd.begin(); it != mapCmd.end(); ++it)
    delete it->second;
}
