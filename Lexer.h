#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Lexer {
 public:
  Lexer() = default;
  ~Lexer() = default;
  vector<string> fileLexer(ifstream &ifs);
  string clearSpaces(string stringToBeCleared);
  string dealWithExpressions(string exp);
};

#endif //LEXER_H