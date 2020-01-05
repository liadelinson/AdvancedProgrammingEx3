#include "Lexer.h"
#include <algorithm>

/**
 * function name: clearSpaces
 * operation: clear useless spaces or tabs at the start and the end of the string
 * input: string - stringToBeCleared
 * @return string
 */
string Lexer::clearSpaces(string stringToBeCleared) {
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

/**
 * function name: dealWithExpressions
 * operation: function that clears spaces and tabs that are in an expression
 * input: string (should be an expression)
 * @return string
 */
string Lexer::dealWithExpressions(string exp) {
  exp = clearSpaces(exp);
  //solution found from https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
  exp.erase(std::remove(exp.begin(), exp.end(), ' '), exp.end());
  exp.erase(std::remove(exp.begin(), exp.end(), '\t'), exp.end());
  return exp;
}

/**
 * function name: fileLexer
 * operation: lexing infile
 * input: ifstream &infile
 * @return vector of strings
 */
vector<string> Lexer::fileLexer(ifstream &infile) {
  int index = 0;
  string loopline = "";
  vector<string> tempVec; //Initialise vector where we'll insert our strings
  string line = "";
  int flag = 0;
  while (getline(infile, line)) {
    flag = 0;
    line = clearSpaces(line);
    if (line == "") {
      continue;
    }
    if (line.substr(0, 20) == "connectControlClient" || line.substr(0, 5) == "Sleep" ||
        line.substr(0, 14) == "openDataServer" || line.substr(0, 5) == "Print") {
      flag = 1;
    } else if (line.substr(0, 3) == "var") {
      tempVec.push_back("var");
      line.erase(0, 4);
      line = clearSpaces(line);
      for (unsigned int i = 0; i < line.length(); i++) {
        if (line.at(i) == '-' && line.at(i + 1) == '>') {
          std::string varName = line.substr(0, i);
          varName = clearSpaces(varName);
          tempVec.push_back(varName);
          line.erase(0, i);
          tempVec.push_back("->");
          line.erase(0, 2);
          line = clearSpaces(line);
          flag = 1;
          continue;
        } else if (line.at(i) == '<' && line.at(i + 1) == '-') {
          std::string varName = line.substr(0, i);
          varName = clearSpaces(varName);
          tempVec.push_back(varName);
          line.erase(0, i);
          tempVec.push_back("<-");
          line.erase(0, 2);
          line = clearSpaces(line);
          flag = 1;
          continue;
        }
          //if line looks like: "var x = ..." where x is the variable and ... is an expression
        else if (line.at(i) == '=') {
          tempVec.push_back(clearSpaces(line.substr(0, i)));
          line.erase(0, i);
          tempVec.push_back("=");
          line.erase(0, 1);
          line = clearSpaces(line);
          line = dealWithExpressions(line);
          tempVec.push_back(line);
          tempVec.push_back("\n");
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
        tempVec.push_back("while");
        line.erase(0, 6);
      } else {
        //if at the start of line
        tempVec.push_back("if");
        line.erase(0, 3);
      }
      line = clearSpaces(line);
      //assuming the line looks like "while/if condition {"
      line = line.substr(0, line.length() - 1);
      size_t pos = line.find(' ');
      tempVec.push_back(dealWithExpressions(line.substr(0, pos)));
      line.erase(0, pos + 1);
      while (line.at(0) == ' ') {
        line.erase(0, 1);
      }
      pos = line.find(' ');
      tempVec.push_back(line.substr(0, pos));
      line.erase(0, pos + 1);
      line = dealWithExpressions(line);
      tempVec.push_back(line);
      tempVec.push_back("{");
      tempVec.push_back("\n");
      continue;
    } else if (line == "}") {
      tempVec.push_back(line);
      tempVec.push_back("\n");
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
      if (partOne != "sim") {
        tempVec.push_back(partOne);
      }
      line.erase(0, count + 1);
      line = clearSpaces(line);
      line.replace(line.length() - 1, 1, "");
      if (partOne == "connectControlClient") {
        int count2 = 1;
        while (line[count2] != '"') {
          count2++;
        }
        tempVec.push_back(line.substr(0, count2 + 1));
        line.erase(0, count2 + 1);
        while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " " ||
            line.substr(0, 1) == ",") {
          line.erase(0, 1);
        }
        line = dealWithExpressions(line);
        tempVec.push_back(line);
      } else {
        //partOne is either sim, Print, openDataServer or Sleep in this case
        if (line.at(0) != '"') {
          line = dealWithExpressions(line);
        }
        tempVec.push_back(line);
      }
      tempVec.push_back("\n");
      continue;
    }
      //in this case the line looks like "variable = expression"
    else {
      index = 0;
      while (line[index] != '=' && line[index] != ' ' && line[index] != '\t') {
        index++;
      }
      tempVec.push_back(line.substr(0, index));
      line.erase(0, index);
      tempVec.push_back("=");
      while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " " ||
          line.substr(0, 1) == "=") {
        line.erase(0, 1);
      }
      tempVec.push_back(dealWithExpressions(line));
      tempVec.push_back("\n");
      continue;
    }
  }
  /*for (auto it : tempVec) {
      cout << it << endl;
  }*/
  return tempVec;
}