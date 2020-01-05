#ifndef LOOPCOMMAND_H
#define LOOPCOMMAND_H

#include "ConditionParser.h"

class LoopCommand : public ConditionParser {
  string type;

 public:
  explicit LoopCommand(string type1);
  int execute(vector<string> cmdTemp, int index) override;
  int enterKey(vector<string> vector, int index) override;
  ~LoopCommand() override = default;
};

#endif //LOOPCOMMAND_H