#ifndef EXPRESSION_H
#define EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() {}
};

#endif //EXPRESSION_H