#include <fstream>
#include <iostream>
#include <chrono>
#include <string.h>
#include <limits.h>
#include "system.h"

using namespace std;

System::System (char* romPath){

  // Reset registers
  pc = 0x200;   // Program Counter to 0x200 (start of userspace)
  I = 0;        // General purpose memory pointer to 0 (initialize value)
  sp = 0;       // Stack pointer to stack frame 0 (stack[0])

  memset(memory, 0, 0x1000);
  frameBuffer.clearScreen();


  // Loads ROM
  ifstream romFile(romPath, ios::in | ios::binary);

  if(romFile.is_open()){
    unsigned short i = pc;

    while(romFile >> noskipws >> memory[i]) {

      i++;
      if(i >= 0x1000) break;

    }
  }

  // Initialize RNG
  rng = mt19937(chrono::system_clock::now().time_since_epoch().count());

}


unsigned char System::rand() {

  return (unsigned char)(rng() % 256);

}


void System::drawScreen() {

  frameBuffer.drawScreen();

}


void System::fetchExecute() {

  // Fetch
  unsigned short instruction = memory[pc] << 8 | memory[pc+1];
  pc += 2;

  // Decode + execute
  unsigned char X = (instruction & 0x0F00) >> 8;
  unsigned char Y = (instruction & 0x00F0) >> 4;
  unsigned char N = instruction & 0x000F;
  unsigned char NN = instruction & 0x00FF;
  unsigned short NNN = instruction & 0x0FFF;

  switch(instruction & 0xF000) {

    case 0x0000:
      switch(instruction) {
        
        case 0x00E0:    // CLS clear screen

          frameBuffer.clearScreen();
          break;

        case 0x00EE:    // RET return

          pc = stack[sp];
          sp--;
          break;
        
      }
      break;

    case 0x1000:        // JP jump

      pc = NNN;
      break;

    case 0x2000:        // CALL call function

      sp++;
      stack[sp] = pc;
      pc = NNN;
      break;

    case 0x3000:        // SE conditional skip if equal

      if(V[X] == NN) pc += 2;
      break;

    case 0x4000:        // SNE conditional skip if not equal

      if(V[X] != NN) pc += 2;
      break;

    case 0x5000:        // SE conditional skip if equal

      if(V[X] == V[Y]) pc += 2;
      break;

    case 0x6000:        // LD load word
    
      V[X] = NN;
      break;
    
    case 0x7000:        // ADD

      V[X] += NN;
      break;
    
    case 0x8000:
      switch(N) {
        
        case 0x0000:    // LD set VX = VY

          V[X] = V[Y];
          break;

        case 0x001:    // OR set VX OR VY
          
          V[X] &= V[Y];
          break;

        case 0x002:    // AND set VX AND VY
          
          V[X] &= V[Y];
          break;
        
        case 0x003:    // XOR set VX XOR VY
          
          V[X] ^= V[Y];
          break;
        
        case 0x004:    // ADD set VX + VY, VF = carry
          
          V[0xF] = (((int)V[X] + (int)V[Y]) / 256) ? 1 : 0;
          V[X] += V[Y];
          break;
        
        case 0x005:    // SUB set VX - VY, VF = NOT borrow
          
          V[0xF] = (V[X] > V[Y]) ? 1 : 0;
          V[X] -= V[Y];
          break;
        
        case 0x006:    // SHR set VF to the least significant bit of VX, then set VX /= 2
          
          V[0xF] = (V[X] & 1) ? 1 : 0;
          V[X] /= 2;
          break;
        
        case 0x007:    // SUBN set VX - VY, VF = NOT borrow
          
          V[0xF] = (V[X] < V[Y]) ? 1 : 0;
          V[X] -= V[Y];
          break;
        
        case 0x00E:    // SHR set VF to the least significant bit of VX, then set VX *= 2
          
          V[0xF] = (V[X] & 128) ? 1 : 0;
          V[X] *= 2;
          break;

      }
      break;

    case 0x9000:        // SNE skip the next instruction if VX != VY

      if(V[X] != V[Y]) pc += 2;
      break;
    
    case 0xA000:        // Set I
    
      I = NNN;
      break;

    case 0xB000:        // JP jump to NNN + V0

      pc = NNN + V[0];
      break;

    case 0xC000:        // RND set V[X] to random uchar AND NN

      V[X] = rand() & NN;
      break;

    case 0xD000:        // DRW draw sprite to screen
      {
        
        unsigned char xCoord = V[X] % SCREEN_WIDTH;
        unsigned char yCoord = V[Y] % SCREEN_HEIGHT;
        
        V[0xF] = 0;

        // Draw sprite
        for(int i = 0; i < N; i++) {
          
          if(yCoord + i >= SCREEN_HEIGHT) break;

          V[0xF] += frameBuffer.setByte(xCoord, yCoord + i, memory[I + i]);

        }

        V[0xF] = V[0xF] ? 1 : 0;      // Set VF properly
        
        frameBuffer.drawScreen();
        break;

      }
    
    default:

      cerr << "Unimplemented instruction encountered: " << std::hex << instruction << endl;
      break;

  }

}
