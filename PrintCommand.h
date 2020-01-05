#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "Command.h"

class PrintCommand : public Command {
 public:
  virtual int execute(vector<string> cmdTemp, int index) override;
  void printMeth(string message);
  string vectorToString(vector<string> vector, int index, int end);
  int enterKey(vector<string> vector, int index);
  ~PrintCommand() override = default;
};
#endif //PRINTCOMMAND_H