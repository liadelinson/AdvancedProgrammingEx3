#include "ex1.h"

double LessOrEqual::calculate() {
  try {
    return ((left->calculate()) <= (right->calculate()));
  }
  catch (const char *e) {
    delete this;
    throw e;
  }
}