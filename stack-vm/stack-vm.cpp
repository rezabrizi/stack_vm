#include "stack-vm.h"

/**
 * Instruction Format
 * header: 2 bits
 * data: 30 bits
 *
 * header format:
 * 0 => positive integer
 * 1 => primitive instruction
 * 2 => negative integer
 * 3 => undefined
 */

// functions
StackVM::StackVM() {
    memory.reserve(1000000);
}

i32 StackVM::getType(i32 instruction) {
    i32 type = 0xc0000000;
    // bitwise and it and shift it by 30 bits
    // every instruction has a 2 bit header
    //
    type = (type & instruction) >> 30;
    return type;
}

i32 StackVM::getData(i32 instruction) {
    i32 data = 0x3fffffff;
    data = data & instruction;
    return data;
}

void StackVM::fetch() {
    pc++;
}

void StackVM::decode() {
    typ = getType(memory[pc]);
    dat = getData(memory[pc]);
}

void StackVM::execute(){
    if (typ == 0 || typ == 2){
        sp++;
        memory[sp] = dat;
    } else {
        doPrimitive();
    }
}


void StackVM::doPrimitive() {
    switch (dat) {
        case 0: //halt
            std::cout << "halt" << std::endl;
            running = 0;
            break;
        case 1: // add
            std::cout << "add " << memory[sp - 1] << " " << memory[sp] << std::endl;
            memory[sp - 1] = memory[sp - 1] + memory[sp];
            sp --;
            break;
        case 2: // sub
            std::cout << "sub " << memory[sp - 1] << " " << memory[sp] << std::endl;
            memory[sp - 1] = memory[sp - 1] - memory[sp];
            sp --;
            break;
        case 3:
            std::cout << "mult " << memory[sp - 1] << " " << memory[sp] << std::endl;
            memory[sp - 1] = memory[sp - 1] * memory[sp];
            sp -- ;
            break;
        case 4: //div
            std::cout << "div " << memory[sp - 1] << " " << memory[sp] << std::endl;
            memory[sp - 1] = memory[sp - 1] / memory[sp];
            sp -- ;
            break;
    }
}

void StackVM::run(){
    pc -= 1;
    while (running == 1){
        fetch();
        decode();
        execute();
        std:: cout << "tos: " << memory[sp] << std::endl;
    }
}

void StackVM::loadProgram(std::vector<i32> program) {
    for (i32 i = 0; i < program.size(); i++){
        memory[pc + i] = program[i];
    }
}
