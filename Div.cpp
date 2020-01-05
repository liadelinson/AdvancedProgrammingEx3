#include "ex1.h"

double Div::calculate() {
  try {
    if ((right->calculate()) != 0) {
      return (left->calculate()) / (right->calculate());
    } else {
      throw "Division by 0 is invalid"; //right->calculate() should be not 0
    }
  }
  catch (const char *e) {
    throw e;
  }
}