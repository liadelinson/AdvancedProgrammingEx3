#include "ex1.h"

Value::Value(const double v) : value(v) {}

double Value::getValue() {
  return this->value;
}

double Value::calculate() {
  return this->getValue();
}





