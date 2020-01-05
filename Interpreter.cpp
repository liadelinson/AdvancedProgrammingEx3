#include "ex1.h"
#include <stack>
#include <queue>

void Interpreter::setVariables(string str) {
  string dataV(str); //converting str to String
  string separator(";"); //variables are separated with ";"
  int pos = 0;//shows current position of the string. size_t is common for array indexing and loop counting
  string curV;//current variable in dataV
  while (!dataV.empty()) {
    if (dataV.find(separator) != string::npos) {
      pos += dataV.find(separator);
    } else {
      pos = dataV.length();
    }
    curV = dataV.substr(0, pos); //curV is the first Variable of DataV in each loop
    string var, value;
    var = curV.substr(0, curV.find("=")); //name of Variable
    value = curV.substr(curV.find("=") + 1); //value of Variable
    if (variables.count(var) == 0) {
      try {
        variables.insert(pair<std::string, double>(var, stod(value))); //inserting variable to the map
      }
      catch (const std::invalid_argument &e) {
        //variable isn't inserted to map because it's invalid
      }
    } else if (variables.count(var) == 1) {
      try {
        variables[var] = stod(value); //updating value of existing variable
      }
      catch (const std::invalid_argument &e) {
        //the "value" isn't a number, so I'll remove the variable from the map
        variables.erase(var);
      }
    }
    dataV.erase(0, pos + separator.length()); //goes to next Variable
    pos = 0;
  }
}

Expression *Interpreter::interpret(string str) {
  string dataE = string(str); //str as string, will be shorten in the while loop
  string originalE = string(str); //str as string, will stay the same, with no changes
  queue<string> outputQueue; //the output of shunting yard algorithm, will be used at the end too
  stack<string> operatorStack; //mainly for shunting yard algorithm
  int curPos = 0; //in originalE string. the minimum value is 0

  //shunting yard algorithm starts here:
  while (!dataE.empty()) {
    if (dataE.substr(0, 1) >= "0" && dataE.substr(0, 1) <= "9") {
      int indexN = 1;
      while ((dataE.substr(indexN - 1, 1) >= "0" && dataE.substr(indexN - 1, 1) <= "9") ||
          (dataE.substr(indexN - 1, 1) == "." && indexN > 1)) {
        //assuming that number is POSITIVE int or double and the string is valid
        indexN++;
      }
      outputQueue.push("NUMBER " + dataE.substr(0, indexN - 1));
      curPos += (indexN - 1);
      dataE = dataE.substr(indexN - 1);
    } else if (dataE.substr(0, 1) == "*" || dataE.substr(0, 1) == "/") {
      if (!operatorStack.empty()) {
        while ((operatorStack.top() == "UPlus" || operatorStack.top() == "UMinus") ||
            (operatorStack.top() == "*" || operatorStack.top() == "/")) {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
          if (operatorStack.empty()) {
            break;
          }
        }
      }
      operatorStack.push(dataE.substr(0, 1));
      curPos++;
      dataE = dataE.substr(1);
    } else if (dataE.substr(0, 1) == "+") {
      //now i'm trying to differentiate between Plus and UPlus
      // (could do the same as UMinus but I assume that if x is a value it'll be written as x and not +x.
      if (curPos == 0) {
        //definitely UPlus
        operatorStack.push("UPlus");
        curPos++;
        dataE = dataE.substr(1);
      } else if (originalE.substr(curPos + 1, 1) == "(" &&
          originalE.substr(curPos - 1, 1) == "(") {
        //definitely UPlus
        operatorStack.push("UPlus");
        curPos++;
        dataE = dataE.substr(1);
      } else {
        //should be Plus
        if (!operatorStack.empty()) {
          while ((operatorStack.top() == "UPlus" || operatorStack.top() == "UMinus") ||
              (operatorStack.top() == "*" || operatorStack.top() == "/") ||
              (operatorStack.top() == "+" || operatorStack.top() == "-")) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
            if (operatorStack.empty()) {
              break;
            }
          }
        }
        operatorStack.push(dataE.substr(0, 1));
        curPos++;
        dataE = dataE.substr(1);
      }
    } else if (dataE.substr(0, 1) == "-") {
      //now i'm trying to differentiate between Minus, UMinus or Negative number
      if (curPos == 0) {
        if (dataE.substr(1, 2) >= "0" && dataE.substr(1, 2) <= "9") {
          int indexNeg = 2;
          while ((dataE.substr(indexNeg - 1, 1) >= "0" && dataE.substr(indexNeg - 1, 1) <= "9")
              || (dataE.substr(indexNeg - 1, 1) == "." && indexNeg > 2)) {
            //assuming that number is NEGATIVE int or double and the string is valid
            indexNeg++;
          }
          outputQueue.push("NUMBER " + dataE.substr(0, indexNeg - 1));
          curPos += (indexNeg - 1);
          dataE = dataE.substr(indexNeg - 1);
        } else {
          //definitely UMinus
          operatorStack.push("UMinus");
          curPos++;
          dataE = dataE.substr(1);
        }
      } else if (originalE.substr(curPos + 1, 1) == "(" &&
          originalE.substr(curPos - 1, 1) == "(") {
        //definitely UMinus
        operatorStack.push("UMinus");
        curPos++;
        dataE = dataE.substr(1);
      } else if (originalE.substr(curPos - 1, 1) == "(") {
        //definitely UMinus
        operatorStack.push("UMinus");
        curPos++;
        dataE = dataE.substr(1);
      } else {
        //should be Minus
        if (!operatorStack.empty()) {
          while ((operatorStack.top() == "UPlus" || operatorStack.top() == "UMinus") ||
              (operatorStack.top() == "*" || operatorStack.top() == "/") ||
              (operatorStack.top() == "+" || operatorStack.top() == "-")) {
            outputQueue.push(operatorStack.top());
            operatorStack.pop();
            if (operatorStack.empty()) {
              break;
            }
          }
        }
        operatorStack.push(dataE.substr(0, 1));
        curPos++;
        dataE = dataE.substr(1);
      }
    }
      /*Addition to ex3: ==,!=,>=,<=,>,<.
        According to https://en.cppreference.com/w/c/language/operator_precedence :
        The precedence of {*,/} > {+,-} > {>=,<=,>,<} > {==,!=} */
    else if (dataE.substr(0, 2) == "==" || dataE.substr(0, 2) == "!=") {
      if (!operatorStack.empty()) {
        while ((operatorStack.top() == "UPlus" || operatorStack.top() == "UMinus") ||
            (operatorStack.top() == "*" || operatorStack.top() == "/") ||
            (operatorStack.top() == "+" || operatorStack.top() == "-") ||
            (operatorStack.top() == "==" || operatorStack.top() == "!=") ||
            (operatorStack.top() == ">" || operatorStack.top() == "<") ||
            (operatorStack.top() == ">=" || operatorStack.top() == "<=")) {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
          if (operatorStack.empty()) {
            break;
          }
        }
      }
      operatorStack.push(dataE.substr(0, 2));
      curPos += 2;
      dataE = dataE.substr(2);
    } else if (dataE.substr(0, 2) == ">=" || dataE.substr(0, 2) == "<=") {
      if (!operatorStack.empty()) {
        while ((operatorStack.top() == "UPlus" || operatorStack.top() == "UMinus") ||
            (operatorStack.top() == "*" || operatorStack.top() == "/") ||
            (operatorStack.top() == "+" || operatorStack.top() == "-") ||
            (operatorStack.top() == ">" || operatorStack.top() == "<") ||
            (operatorStack.top() == ">=" || operatorStack.top() == "<=")) {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
          if (operatorStack.empty()) {
            break;
          }
        }
      }
      operatorStack.push(dataE.substr(0, 2));
      curPos += 2;
      dataE = dataE.substr(2);
    } else if (dataE.substr(0, 1) == ">" || dataE.substr(0, 1) == "<") {
      if (!operatorStack.empty()) {
        while ((operatorStack.top() == "UPlus" || operatorStack.top() == "UMinus") ||
            (operatorStack.top() == "*" || operatorStack.top() == "/") ||
            (operatorStack.top() == "+" || operatorStack.top() == "-") ||
            (operatorStack.top() == ">" || operatorStack.top() == "<") ||
            (operatorStack.top() == ">=" || operatorStack.top() == "<=")) {
          outputQueue.push(operatorStack.top());
          operatorStack.pop();
          if (operatorStack.empty()) {
            break;
          }
        }
      }
      operatorStack.push(dataE.substr(0, 1));
      curPos++;
      dataE = dataE.substr(1);
    } else if (dataE.substr(0, 1) == "(") {
      operatorStack.push("(");
      curPos++;
      dataE = dataE.substr(1);
    } else if (dataE.substr(0, 1) == ")") {
      while (operatorStack.top() != "(" && !operatorStack.empty()) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
      }
      if (!operatorStack.empty()) {
        if (operatorStack.top() == "(") {
          operatorStack.pop();
          curPos++;
          dataE = dataE.substr(1);
        }
      } else {
        //"(" and ")" should always match
        throw "there are mismatched parentheses";
      }
    } else {
      //for variables
      unsigned int indexV = 1;
      while (dataE.substr(indexV - 1, 1) != "+" && dataE.substr(indexV - 1, 1) != "-" &&
          dataE.substr(indexV - 1, 1) != "*" && dataE.substr(indexV - 1, 1) != "/" &&
          dataE.substr(indexV - 1, 2) != "==" && dataE.substr(indexV - 1, 2) != "!=" &&
          dataE.substr(indexV - 1, 2) != ">=" && dataE.substr(indexV - 1, 1) != "<=" &&
          dataE.substr(indexV - 1, 1) != ">" && dataE.substr(indexV - 1, 1) != "<" &&
          dataE.substr(indexV - 1, 1) != "(" && dataE.substr(indexV - 1, 1) != ")") {
        indexV++;
        if (indexV > dataE.length()) {
          break;
        }
      }
      //checking if the current variable is actually a variable in the map of variables:
      if (variables.count(dataE.substr(0, indexV - 1)) > 0) {
        outputQueue.push("VARIABLE " + dataE.substr(0, indexV - 1));
        curPos += indexV - 1;
        dataE = dataE.substr(indexV - 1);
      } else {
        //variables should include all variables that appears in interpret
        throw "no match between setVariables and interpret";
      }
    }
  }
  //the end of shunting yard algorithm
  while (operatorStack.size() > 0) {
    outputQueue.push(operatorStack.top());
    operatorStack.pop();
  }
  //now I can use the outputQueue:
  stack<Expression *> expressions;
  while (!outputQueue.empty()) {
    //outputQueue can include Value, Variable, Unary and Binary operators
    if (outputQueue.front().find("NUMBER ") == 0) {
      //pushing the value to the stack
      expressions.push(new Value(stod(outputQueue.front().substr(7))));
      outputQueue.pop();
    } else if (outputQueue.front().find("VARIABLE ") == 0) {
      //pushing the variable to the stack
      string variableName = outputQueue.front().substr(9);
      double variableValue = variables[variableName];
      Variable *v = new Variable(variableName, variableValue);
      expressions.push(v);
      outputQueue.pop();
    } else {
      if (outputQueue.front() == "UPlus" || outputQueue.front() == "UMinus") {
        Expression *exp = expressions.top();
        expressions.pop();
        if (outputQueue.front() == "UPlus") {
          expressions.push(new UPlus(exp));
        } else {
          expressions.push(new UMinus(exp));
        }
        outputQueue.pop();
      }
        //the other options are binary operators
      else {
        Expression *exp1 = expressions.top();
        expressions.pop();
        Expression *exp2 = expressions.top();
        expressions.pop();
        if (outputQueue.front() == "+") {
          expressions.push(new Plus(exp2, exp1));
        } else if (outputQueue.front() == "-") {
          expressions.push(new Minus(exp2, exp1));
        } else if (outputQueue.front() == "*") {
          expressions.push(new Mul(exp2, exp1));
        } else if (outputQueue.front() == "/") {
          expressions.push(new Div(exp2, exp1));
        } else if (outputQueue.front() == "==") {
          expressions.push(new EqualTo(exp2, exp1));
        } else if (outputQueue.front() == "!=") {
          expressions.push(new NotEqualTo(exp2, exp1));
        } else if (outputQueue.front() == ">") {
          expressions.push(new GreaterThan(exp2, exp1));
        } else if (outputQueue.front() == "<") {
          expressions.push(new LessThan(exp2, exp1));
        } else if (outputQueue.front() == ">=") {
          expressions.push(new GreaterOrEqual(exp2, exp1));
        } else if (outputQueue.front() == "<=") {
          expressions.push(new LessOrEqual(exp2, exp1));
        }
        outputQueue.pop();
      }//binary operators
    }//operators
  }//using the outputQueue
  return expressions.top();
}