#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H

#include "Command.h"

class ConnectCommand : public Command {

 public:
  int execute(vector<string> cmdTemp, int index) override;
  void connectSocket(int port, string ip);
  static void *updateVal(void *args);
  int enterKey(vector<string> cmdTemp, int index);
  string vectorToString(vector<string> vector, int index, int end);
  ~ConnectCommand() override = default;
};

#endif //CONNECTCOMMAND_H