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
    std::list<std::string> finalList;
    void readFile(std::fstream& file) {
        std::string line;
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        while (std::getline(file, line)) {
            if (line.substr(0, 1) == "\t") {
                line.erase(0, 1);
            }
            if (line.substr(0, 5) == "Print") {
                finalList.insert(finalList.end(), "Print");
                line.erase(0, 6);
                line.replace(line.length()-1, 1, "");
                finalList.insert(finalList.end(), line);
                continue;
            }
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                parseString(finalList,finalList.end(), token);
                line.erase(0, pos + delimiter.length());
            }
            finalList.end(), parseString(finalList,finalList.end(), line);
        }
    }

    void printall() {
        for (auto it = finalList.begin(); it != finalList.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }

    void parseString(std::list<std::string> strList,std::list<std::string>::iterator it ,std::string stringToParse) {
        if (stringToParse[stringToParse.length() - 1] == ')') {
            int count = 0;
            while (stringToParse[count] != '(') {
                count++;
            }
            std::string partOne = stringToParse.substr(0, count);
            strList.insert(it, partOne);
            //std::cout << partOne << std::endl;
            stringToParse.erase(0, count + 1);
            stringToParse.replace(stringToParse.length()-1 ,1 ,"");
        }
        //std::cout << stringToParse << std::endl;
        strList.insert(it, stringToParse);
    }
};

#endif //CPPEX3_LEXER_H
