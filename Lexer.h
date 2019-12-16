//
// Created by sharon on 12/11/19.
//

#ifndef CPPEX3_LEXER_H
#define CPPEX3_LEXER_H

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

class Lexer {
 public:
  std::list<std::string> finalList; //finalList needs to be not empty at the start
  void readFile(std::fstream &file) {
    std::string line;
    int flag;
    while (std::getline(file, line)) {
      flag = 0;
      line = clearSpaces(line);
      if (line == "") {
        continue;
      }
      if (line.substr(0, 20) == "connectControlClient" || line.substr(0, 5) == "Sleep" ||
          line.substr(0, 14) == "openDataServer" || line.substr(0, 5) == "Print") {
        flag = 1;
      }
      //if the line starts with var
      else if (line.substr(0, 3) == "var") {
        finalList.insert(finalList.end(), "var");
        line.erase(0, 4);
        line = clearSpaces(line);
        for (unsigned int i = 0; i < line.length(); i++) {
          if (line.at(i) == '-' && line.at(i + 1) == '>') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            finalList.insert(finalList.end(), "->");
            line.erase(0, 2);
            line = clearSpaces(line);
            flag = 1;
            continue;
          } else if (line.at(i) == '<' && line.at(i + 1) == '-') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            finalList.insert(finalList.end(), "<-");
            line.erase(0, 2);
            line = clearSpaces(line);
            flag = 1;
            continue;
          }
            //if line looks like: "var x = ..." where x is the variable and ... is an expression
          else if (line.at(i) == '=') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            finalList.insert(finalList.end(), "=");
            line.erase(0, 1);
            line = clearSpaces(line);
            line = dealWithExpressions(line);
            finalList.insert(finalList.end(), line);
            continue;
          }
        }
        //if the line looks like "var x = ..." it's possible to continue to the next line
        if (!flag) {
          continue;
        }
      }//if the line starts with var

      //if the line starts with while or if
      else if (line.substr(0, 5) == "while" || line.substr(0, 2) == "if") {
        if (line.substr(0, 5) == "while") {
          finalList.insert(finalList.end(), "while");
          line.erase(0, 6);
        } else {
          //if at the start of line
          finalList.insert(finalList.end(), "if");
          line.erase(0, 3);
        }
        line = clearSpaces(line);
        //assuming the line looks like "while/if condition {"
        line = line.substr(0, line.length() - 1);
        line = clearSpaces(line);
        line = dealWithExpressions(line);
        finalList.insert(finalList.end(), line);
        finalList.insert(finalList.end(), "{");
        continue;
      } else if (line == "}") {
        finalList.insert(finalList.end(), line);
        continue;
      }

      //if flag == 1 it means the line currently looks like something(...)
      //assumption: there are no variables that their name is something like "PrintABC"
      if (flag) {
        int count = 0;
        while (line[count] != '(') {
          count++;
        }
        std::string partOne = line.substr(0, count);
        finalList.insert(finalList.end(), partOne);
        line.erase(0, count + 1);
        line = clearSpaces(line);
        line.replace(line.length() - 1, 1, "");
        if (partOne == "connectControlClient") {
          int count2 = 1;
          while (line[count2] != '"') {
            count2++;
          }
          finalList.insert(finalList.end(), line.substr(0, count2 + 1));
          line.erase(0, count2 + 1);
          while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " " ||
              line.substr(0, 1) == ",") {
            line.erase(0, 1);
          }
          line = dealWithExpressions(line);
          finalList.insert(finalList.end(), line);
        } else {
          //partOne is either sim, Print, openDataServer or Sleep in this case
          if (line.at(0) != '"') {
            line = dealWithExpressions(line);
          }
          finalList.insert(finalList.end(), line);
        }
        continue;
      }
      //in this case the line looks like "variable = expression"
      else {
        int index = 0;
        while (line[index] != '=' && line[index] != ' ' && line[index] != '\t') {
          index++;
        }
        finalList.insert(finalList.end(), line.substr(0, index));
        line.erase(0, index);
        finalList.insert(finalList.end(), "=");
        while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " " ||
            line.substr(0, 1) == "=") {
          line.erase(0, 1);
        }
        line = dealWithExpressions(line);
        finalList.insert(finalList.end(), line);
        continue;
      }
    }
  }

  void printAll() {
    for (auto it = finalList.begin(); it != finalList.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }

  //function that clears spaces and tabs from the start and end of the string it gets as a parameter.
  std::string clearSpaces(std::string stringToBeCleared) {
    //in case there are useless spaces or tabs at the start of string
    while (stringToBeCleared.substr(0, 1) == "\t" || stringToBeCleared.substr(0, 1) == " ") {
      stringToBeCleared.erase(0, 1);
    }
    //in case there are useless spaces or tabs at the end of string
    while (stringToBeCleared.back() == '\t' || stringToBeCleared.back() == ' ') {
      stringToBeCleared = stringToBeCleared.substr(0, stringToBeCleared.length() - 1);
    }
    return stringToBeCleared;
  }

  //function that clears spaces and tabs that are in an expression
  std::string dealWithExpressions(std::string exp) {
    exp = clearSpaces(exp);
    //solution found from https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
    exp.erase(std::remove(exp.begin(), exp.end(), ' '), exp.end());
    exp.erase(std::remove(exp.begin(), exp.end(), '\t'), exp.end());
    return exp;
  }
};

#endif //CPPEX3_LEXER_H
