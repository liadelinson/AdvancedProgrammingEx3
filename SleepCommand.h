#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H

#include "Command.h"

class SleepCommand : public Command {
 public:
  int execute(vector<string> cmdTemp, int index) override;
  string vectorToString(vector<string> vector, int index, int end);
  int enterKey(vector<string> vector, int index);

};
#endif //SLEEPCOMMAND_H
