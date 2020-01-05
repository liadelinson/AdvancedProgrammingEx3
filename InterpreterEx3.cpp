#include "InterpreterEx3.h"
#include "GlobalTables.h"
#include "ex1.h"

/**
 * function name: setVariables
 * operation: returning string of variables that are in the expression of calculateExpression
 * input: string str2 - the expression
 * @return string - list of variables
 */
string InterpreterEx3::setVariables(string str2) {
  string list;
  for (auto x : symbolTable) {
    if (str2.find(x.first) != std::string::npos) {
      list += x.first;
      list += "=";
      list += to_string(x.second);
      list += ";";
    }
  }
  if (list.back() == ';') {
    list = list.substr(0, list.size() - 1);
  }
  return list;
}

/**
 * function name: calculateExpression
 * operation: calculating str1 (which is an expression) by using classes from ex1
 * input: string str1 - an expression
 * @return double - result of the expression
 */
double InterpreterEx3::calculateExpression(string str1) {
  Interpreter *iEx1 = new Interpreter();
  Expression *exp = nullptr;
  double result = 0;
  string listOfVariables = setVariables(str1);
  //cout << listOfVariables << endl;
  try {
    iEx1->setVariables(listOfVariables);
    exp = iEx1->interpret(str1);
    result = exp->calculate();
    delete exp;
    delete iEx1;
  } catch (const char *e) {
    if (exp != nullptr) {
      delete exp;
    }
    if (iEx1 != nullptr) {
      delete iEx1;
    }
    throw e;
  }
  return result;
}