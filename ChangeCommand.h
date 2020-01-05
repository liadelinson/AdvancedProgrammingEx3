#ifndef CHANGECOMMAND_H
#define CHANGECOMMAND_H

#include "Command.h"

class ChangeCommand : public Command {
 public:
  int execute(vector<string> cmdTemp, int index) override;
  void changeData(string location, string nValue);
  int enterKey(vector<string> cmdTemp, int index);
  string vectorToString(vector<string> vector, int index, int end);
  ~ChangeCommand() override = default;
};

#endif //CHANGECOMMAND_H
