#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "ex1.h"

using namespace std;

void testLexer();
void testEx1();

int main() {
  testLexer();
  testEx1();
  return 0;
}



void testLexer()
{
  Lexer *lexer = new Lexer();
  fstream fs("../fly.txt");
  lexer->readFile(fs);
  lexer->printAll();
  fs.close();
}

void testEx1()
{
  Interpreter* i = new Interpreter();
  Expression* e = nullptr;
  try {
    i->setVariables("x=14;y=8");
    e = i->interpret("(7*(x+5)<=(y+11)/5)==(8-y)");
    std::cout << "result: " << e->calculate() << std::endl;
    delete e;
    delete i;
  } catch (const char* e) {
    if (e != nullptr) {
      delete e;
    }
    if (i != nullptr) {
      delete i;
    }
    std::cout << e << std::endl;
  }
}