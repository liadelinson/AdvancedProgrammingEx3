#include "ex1.h"

double UPlus::calculate() {
  try {
    return exp->calculate();
  }
  catch (const char *e) {
    delete this;
    throw e;
  }
}



