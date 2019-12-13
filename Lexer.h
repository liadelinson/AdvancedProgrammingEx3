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

class Lexer {
 public:
  std::list<std::string> finalList{"Start"}; //finalList needs to be not empty at the start
  void readFile(std::fstream &file) {
    std::string line;
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int flag;
    while (std::getline(file, line)) {
      flag = 1;
      //if we passed the start and there are strings in finalList, "Start" can be removed from there.
      if(finalList.size() >= 2 && finalList.front() == "Start")
      {
        finalList.erase(finalList.begin());
      }
      //ignoring tabs or spaces at the start of line:
      while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
        line.erase(0, 1);
      }
      //if the line looks like "Print("...")" we don't need the brackets
      if (line.substr(0, 5) == "Print") {
        finalList.insert(finalList.end(), "Print");
        line.erase(0, 6);
        line.replace(line.length() - 1, 1, "");
        finalList.insert(finalList.end(), line);
        continue;
      }
        //if the line starts with var
      else if (line.substr(0, 3) == "var") {
        finalList.insert(finalList.end(), "var");
        line.erase(0, 4);
        //in case there are another spaces or tabs after "var"
        while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
          line.erase(0, 1);
        }
        for (int i = 0; i < line.length(); i++) {
          if (line.at(i) == '-' && line.at(i + 1) == '>') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            finalList.insert(finalList.end(), "->");
            line.erase(0, 2);
            while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
              line.erase(0, 1);
            }
            continue;
          } else if (line.at(i) == '<' && line.at(i + 1) == '-') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            finalList.insert(finalList.end(), "<-");
            line.erase(0, 2);
            while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
              line.erase(0, 1);
            }
            continue;
          }
            //if line looks like: "var x = ..." where x is the variable and ... is an expression
          else if (line.at(i) == '=') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            finalList.insert(finalList.end(), "=");
            line.erase(0, 1);
            while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
              line.erase(0, 1);
            }
            finalList.insert(finalList.end(), line);
            line.erase(0, line.length());
            flag = 0;
            continue;
          } else if (line.at(i) == ' ' || line.at(i) == '\t') {
            finalList.insert(finalList.end(), line.substr(0, i));
            line.erase(0, i);
            while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
              line.erase(0, 1);
            }
            //assuming after name of variable only "->", "<-" or "=" can appear
            if (line.at(0) == '-' && line.at(1) == '>') {
              finalList.insert(finalList.end(), "->");
              line.erase(0, 2);
              while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
                line.erase(0, 1);
              }
              continue;
            } else if (line.at(0) == '<' && line.at(1) == '-') {
              finalList.insert(finalList.end(), "<-");
              line.erase(0, 2);
              while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
                line.erase(0, 1);
              }
              continue;
            } else if (line.at(0) == '=') {
              finalList.insert(finalList.end(), "=");
              line.erase(0, 1);
              while (line.substr(0, 1) == "\t" || line.substr(0, 1) == " ") {
                line.erase(0, 1);
              }
              finalList.insert(finalList.end(), line);
              line.erase(0, line.length());
              flag = 0;
              continue;
            }
          }
        }
      }//if the line starts with var
      if (flag || line.substr(0, 3) == "sim" || line.substr(0, 14) == "openDataServer" ||
          line.substr(0, 20) == "connectControlClient" || line.substr(0, 5) == "Sleep") {
        //the tokens are separated by delimiter which is " "
        /*while ((pos = line.find(delimiter)) != std::string::npos) {
          token = line.substr(0, pos);
          parseString(finalList, finalList.end(), token);
          line.erase(0, pos + delimiter.length());
        }*/
        finalList.end(), parseString(finalList, finalList.end(), line);
      }
    }
  }

  void printall() {
    for (auto it = finalList.begin(); it != finalList.end(); ++it) {
      std::cout << *it << std::endl;
    }
  }

  //dealing with lines like open openDataServer where we dont want brackets to be in final list
  void parseString(std::list<std::string> strList, std::list<std::string>::iterator it, std::string stringToParse) {
    if (stringToParse[stringToParse.length() - 1] == ')') {
      int count = 0;
      while (stringToParse[count] != '(') {
        count++;
      }
      std::string partOne = stringToParse.substr(0, count);
      strList.insert(it, partOne);
      stringToParse.erase(0, count + 1);
      stringToParse.replace(stringToParse.length() - 1, 1, "");
      while (stringToParse.substr(0, 1) == "\t" || stringToParse.substr(0, 1) == " ") {
        stringToParse.erase(0, 1);
      }
      if (partOne == "sim") {
        strList.insert(it, stringToParse);
        stringToParse.erase(0, stringToParse.length());
      } else if (partOne == "openDataServer" || partOne == "Sleep") {
        strList.insert(it, stringToParse);
        stringToParse.erase(0, stringToParse.length());
      } else if (partOne == "connectControlClient") {
        int count2 = 1;
        while (stringToParse[count2] != '"') {
          count2++;
        }
        strList.insert(it, stringToParse.substr(0, count2 + 1));
        stringToParse.erase(0, count2 + 1);
        while (stringToParse.substr(0, 1) == "\t" || stringToParse.substr(0, 1) == " " ||
            stringToParse.substr(0, 1) == ",") {
          stringToParse.erase(0, 1);
        }
        strList.insert(it, stringToParse);
        stringToParse.erase(0, stringToParse.length());
      }
    }
    //in this case the line looks like "variable = expression"
    else if(stringToParse.substr(0,2) != "if" && stringToParse.substr(0,5) != "while" &&
            stringToParse != "}")
    {
      int index = 0;
      while (stringToParse[index] != '=' && stringToParse[index] != ' ' && stringToParse[index] != '\t') {
        index++;
      }
      strList.insert(it, stringToParse.substr(0, index));
      stringToParse.erase(0, index);
      strList.insert(it, "=");
      while (stringToParse.substr(0, 1) == "\t" || stringToParse.substr(0, 1) == " " ||
          stringToParse.substr(0, 1) == "=") {
        stringToParse.erase(0, 1);
      }
      strList.insert(it, stringToParse);
    }

    else {
      strList.insert(it, stringToParse);
    }

  }
};

#endif //CPPEX3_LEXER_H
