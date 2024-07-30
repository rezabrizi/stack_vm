cmake_minimum_required(VERSION 3.27)
project(stack_virtual_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(stack_virtual_machine stack-vm/main.cpp
        stack-vm/stack-vm.h
        stack-vm/stack-vm.cpp
        sasm/lexer.h
        sasm/Lexer.cpp)
