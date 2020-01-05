#include "Lexer.h"
#include "Parser.h"

int main(int argc, char **argv) {
  if (argc >= 1) {
    Parser *p = new Parser();
    Lexer *l = new Lexer();
    vector<string> stringVec;
    ifstream infile(argv[1]);
    stringVec = l->fileLexer(infile);
    infile.close();
    try {
      p->strPrs(stringVec);
    }
    catch (const char *e) {
      delete p;
      delete l;
      cout << e << endl;
      return -1;
    }
    delete p;
    delete l;
  } else {
    cout << "Error: file name is not provided from args" << endl;
  }
  return 0;
}