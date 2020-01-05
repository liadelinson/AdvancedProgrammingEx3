#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser {
 public:
  int execute(vector<string> cmdTemp, int index) override;
  int enterKey(vector<string> vector, int index) override;
  ~IfCommand() override = default;
};

#endif //IFCOMMAND_H