cmake_minimum_required(VERSION 3.12)
project(cppEx3)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(cppEx3 main.cpp Parser.cpp Parser.h Lexer.cpp Lexer.h Command.h ConnectCommand.cpp OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.h VarCommand.cpp VarCommand.h PrintCommand.cpp PrintCommand.h LoopCommand.cpp LoopCommand.h GlobalTables.cpp GlobalTables.h ChangeCommand.cpp ChangeCommand.h ConditionParser.cpp ConditionParser.h SleepCommand.cpp SleepCommand.h IfCommand.cpp IfCommand.h IfCommand.h Expression.h ex1.h Value.cpp Variable.cpp BinaryOperator.cpp UnaryOperator.cpp UPlus.cpp UMinus.cpp Plus.cpp Minus.cpp Mul.cpp Div.cpp Interpreter.cpp EqualTo.cpp NotEqualTo.cpp GreaterThan.cpp LessThan.cpp GreaterOrEqual.cpp LessOrEqual.cpp InterpreterEx3.h InterpreterEx3.cpp)