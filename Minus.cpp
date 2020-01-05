#include "ex1.h"

double Minus::calculate() {
  try {
    return (left->calculate()) - (right->calculate());
  }
  catch (const char *e) {
    delete this;
    throw e;
  }
}