#include "ex1.h"

UnaryOperator::UnaryOperator(Expression *e) {
  exp = e;
}

//this calculate will be overridden
double UnaryOperator::calculate() {
  return 0;
}

UnaryOperator::~UnaryOperator() {
  delete exp;
}

