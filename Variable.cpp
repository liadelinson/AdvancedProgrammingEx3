#include "ex1.h"

Variable::Variable(std::string n, double v) {
  name = n;
  value = v;
}

double Variable::getValue() {
  return this->value;
}

Variable &Variable::operator++(int x) {
  int temp = x; //used to avoid warnings of [-Wunused-parameter]
  this->value++;
  this->value += temp;
  this->value -= temp;
  return *this;
}

Variable &Variable::operator--(int x) {
  int temp = x; //used to avoid warnings of [-Wunused-parameter]
  this->value--;
  this->value += temp;
  this->value -= temp;
  return *this;
}

Variable &Variable::operator+=(double a) {
  this->value += a;
  return *this;
}

Variable &Variable::operator-=(double a) {
  this->value -= a;
  return *this;
}

Variable &Variable::operator++() {
  this->value++;
  return *this;
}

Variable &Variable::operator--() {
  this->value--;
  return *this;
}

double Variable::calculate() {
  return this->getValue();
}



