#ifndef VARCOMMAND_H
#define VARCOMMAND_H

#include "Command.h"

class VarCommand : public Command {
 public:
  int execute(vector<string> cmdTemp, int index) override;
  void bind(string location, string var);
  void toSim(string location, string var);
  void bindSet(string var, string value);
  int enterKey(vector<string> cmdTemp, int index);
  string vectorToString(vector<string> vector, int i, int anEnd);
  ~VarCommand() override = default;
};

#endif //VARCOMMAND_H
