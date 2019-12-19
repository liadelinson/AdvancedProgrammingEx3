#ifndef EX1_EX1_H
#define EX1_EX1_H

#include "Expression.h"
#include <string>
#include <map>

class Value : public Expression {
 private:
  const double value; //value of the class Value
 public:
  Value(double v); //constructor of Value that gets a double
  double getValue(); //getter of the value, also const to make it immutable
  double calculate() override; //returns the value (uses the getter)
};

class Variable : public Expression {
 private:
  std::string name; //name of variable
  double value; //value of variable
 public:
  Variable(std::string n, double v); //constructor that gets the name and the value of the Variable
  double getValue();
  Variable &operator++(int x); // overloading postfix ++
  Variable &operator--(int x); // overloading postfix --
  Variable &operator+=(double a); // overloading +=
  Variable &operator-=(double a); // overloading -=
  Variable &operator++(); // overloading prefix ++
  Variable &operator--(); // overloading prefix --
  double calculate() override; //returns the value of the variable
};

class UnaryOperator : public Expression {
 protected:
  Expression *exp; //the only expression in UnaryOperator. it's protected because of UPlus and UMinus:
 public:
  UnaryOperator(Expression *e); //constructor that gets the only expression in UnaryOperator
  double calculate() override;
  ~UnaryOperator() override;
};

class BinaryOperator : public Expression {
 protected:
  //the 2 expressions in BinaryOperator. it's protected because of Plus, Minus, Mul and Div classes:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *l, Expression *r); //constructor that gets the 2 expressions in BinaryOperator
  double calculate() override;
  ~BinaryOperator() override;
};

//UPlus - returns the expression itself
class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *e) : UnaryOperator(e) {} //using the constructor of UnaryOperator (*exp is protected)
  double calculate() override;
};

//UMinus - returns the negative of the expression
class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *e) : UnaryOperator(e) {} //using the constructor of UnaryOperator (*exp is protected)
  double calculate() override;
};

//Plus - basically represents left + right
class Plus : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  Plus(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this Plus expression
};

//Minus - basically represents left - right
class Minus : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  Minus(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this Minus expression

};

//Mul - basically represents left * right
class Mul : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  Mul(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this Mul expression

};

//Div - basically represents left / right
class Div : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  Div(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this Div expression
};


//EqualTo - basically represents left == right
class EqualTo : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  EqualTo(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this EqualTo expression
};

//NotEqualTo - basically represents left != right
class NotEqualTo : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  NotEqualTo(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this NotEqualTo expression
};

//GreaterThan - basically represents left > right
class GreaterThan : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  GreaterThan(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this GreaterThan expression
};

//LessThan - basically represents left < right
class LessThan : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  LessThan(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this LessThan expression
};

//GreaterOrEqual - basically represents left >= right
class GreaterOrEqual : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  GreaterOrEqual(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this GreaterOrEqual expression
};

//LessOrEqual - basically represents left <= right
class LessOrEqual : public BinaryOperator {
 public:
  //using the constructor of BinaryOperator (*left and *right are protected):
  LessOrEqual(Expression *l, Expression *r) : BinaryOperator(l, r) {}
  double calculate() override; //returns the result of this LessOrEqual expression
};



class Interpreter {
 private:
  //map of variables (keys are names, values are the values of variables), changed by setVariables
  std::map<std::string, double> variables;

 public:
  void setVariables(std::string str); //add variables or change values if it's possible and valid
  /*converting an expression from char* to Expression* so it'll be possible to calculate it.
    it also throws const char* in case of an exception */
  Expression *interpret(std::string str);
};

#endif //EX1_EX1_H
