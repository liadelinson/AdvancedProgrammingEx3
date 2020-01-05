Advanced Programming 1 - Ex3 - Flight Simulator Interpreter

# How to run the project:
compiling and then running by writing "./a.out file_name"

**The file should be put at the same directory where the project is running

# The project includes the following files:
  - Ex3 files - files that are relevant or more interesting for ex3
  - Ex1 files - another files that were in ex1 or related to that, in terms of dealing with expressions
  - details.txt
  - README.md (this file)

# Ex3 files:
  .h files:
    - Lexer.h   
    - Parser.h   
    - GlobalTables.h 
    - Command.h   
    - ConnectCommand.h   
    - OpenServerCommand.h
    - VarCommand.h
    - ChangeCommand.h    
    - SleepCommand.h 
    - PrintCommand.h 
    - ConditionParser.h 
    - IfCommand.h   
    - LoopCommand.h      
    - InterpreterEx3.h    
    
  .cpp files:
    - main.cpp - running the whole program by using a lexer and a parser
    - Lexer.cpp - lexing the given file as an argument  
    - Parser.cpp - after lexing, this class should run the commands that are written in file
    - GlobalTables.cpp - class that includes tables (kind of database) and global info
    - ConnectCommand.cpp - dealing with connection
    - OpenServerCommand.cpp - dealing with opening server
    - VarCommand.cpp - dealing with lines that start with var
    - ChangeCommand.cpp - dealing with lines like: "variable_name = expression"
    - SleepCommand.cpp - dealing with sleep commands
    - PrintCommand.cpp - dealing with print commands
    - ConditionParser.cpp - type of a command that deals with a case when commands depend on a condition to be done
    - IfCommand.cpp - deals with If scenarios, inherits from ConditionParser
    - LoopCommand.cpp - deals with While scenarios, inherits from ConditionParser   
    - InterpreterEx3.cpp - Interpreter that uses Interpreter class, but is specifically for ex3    
  
                          
# Ex1 files:
  .h files:
    - ex1.h
    - Expression.h
    
  .cpp files:
    - UnaryOperator.cpp
    - BinaryOperator.cpp  
    - Value.cpp 
    - Variable.cpp
    - UPlus.cpp 
    - UMinus.cpp 
    - Plus.cpp  
    - Minus.cpp 
    - Mul.cpp 
    - Div.cpp  
    - EqualTo.cpp
    - NotEqualTo.cpp  
    - GreaterThan.cpp  
    - GreaterOrEqual.cpp 
    - LessThan.cpp  
    - LessOrEqual.cpp 
    - Interpreter.cpp  


# Things to be taken into consideration
  - You might not use the simulator while checking, but the program should work pretty good
    there (using fly.txt), which means our program is somewhat good if there are any complications...
    
  - The program expects to get exactly 36 values (as you said), go to OpenServerCommand.cpp, 
    to buffToDouble function to see why.
    
 
  
  
  
  
  
   
      
    
                
       
 
    
    
  
  
