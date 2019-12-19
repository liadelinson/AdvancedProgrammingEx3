#include "ex1.h"

BinaryOperator::BinaryOperator(Expression *l, Expression *r) {
  left = l;
  right = r;
}

//this calculate will be overridden
double BinaryOperator::calculate() {
  return 0;
}

BinaryOperator::~BinaryOperator() {
  delete left;
  delete right;
}

