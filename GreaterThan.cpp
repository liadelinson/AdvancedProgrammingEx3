//
// Created by liad on 19/12/2019.
//
#include "ex1.h"

double GreaterThan::calculate() {
  try {
    return ((left->calculate()) > (right->calculate()));
  }
  catch (const char *e) {
    delete this;
    throw e;
  }
}


