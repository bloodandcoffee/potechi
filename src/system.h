#ifndef SYSTEM_H
#define SYSTEM_H

class System {

    // Memory and general purpose registers
    unsigned char memory[0x1000];
    unsigned char V[0x10];

    // Special purpose registers
    unsigned short I;
    unsigned char delay, sound;
    unsigned short pc;

    // Stack
    unsigned short stack[16];
    unsigned char sp;

    public:
    char frameBuffer[128][64];

    void loadProgram(char* romPath);
    void fetchExecute();

};


#endif