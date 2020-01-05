#include "ex1.h"

double Mul::calculate() {
  try {
    return (left->calculate()) * (right->calculate());
  }
  catch (const char *e) {
    delete this;
    throw e;
  }
}