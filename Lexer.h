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
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                finalList.insert(finalList.end(), parseString(token));
                line.erase(0, pos + delimiter.length());
            }
            finalList.insert(finalList.end(), parseString(line));
        }
    }

    void printall() {
        for (auto it = finalList.begin(); it != finalList.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }

    std::string parseString(std::string stringToParse) {
        if (stringToParse[stringToParse.length() - 1] == ')') {
            int count = 0;
            while (stringToParse[count] != '(') {
                count++;
            }
            stringToParse.erase(0, count + 1);
            stringToParse.replace(stringToParse.length()-1, 1, "");
        }
        std::cout << stringToParse << std::endl;
        return stringToParse;
    }
};

#endif //CPPEX3_LEXER_H
