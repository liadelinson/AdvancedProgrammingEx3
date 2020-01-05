#include "ex1.h"

double UMinus::calculate() {
  try {
    Expression *negative = new Value(-1);
    Expression *expValue = new Value(exp->calculate());
    Expression *sameExp = new Mul(negative, expValue); //-exp can be treated as -1*exp
    double result = sameExp->calculate();
    delete sameExp;
    return result;
  }
  catch (const char *e) {
    delete this;
    throw e;
  }
}