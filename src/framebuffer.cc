#include <iostream>
#include <string.h>
#include <curses.h>
#include "framebuffer.h"

using namespace std;

// Debugging implementation
void FrameBuffer::drawScreen() {

  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    for(int j = 0; j < (SCREEN_WIDTH / 8); j++) {

      for(int h = 0; h < 8; h++) {

        if(frameBuffer[j][i] >> (7 - h) & 0x1) {
          mvaddch(i+1, 2*(j*8 + h) + 1, (char)219);
          mvaddch(i+1, 2*(j*8 + h) + 2, (char)219);
        } else {
          mvaddch(i+1, 2*(j*8 + h) + 1, (char)32);
          mvaddch(i+1, 2*(j*8 + h) + 2, (char)32);
        }
        
      }

    }
  }

  refresh();

}

void FrameBuffer::clearScreen() {

  memset(frameBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
  drawScreen();

}

bool FrameBuffer::setByte(unsigned char x, unsigned char y, unsigned char val) {

  // Do not go offscreen
  if(x >= SCREEN_WIDTH) return false;
  if(y >= SCREEN_HEIGHT) return false;

  bool retVal = false;

  unsigned char old;
  const unsigned char xCoord = x / 8;

  const unsigned char leftHalf = val >> (x % 8);
  const unsigned char rightHalf = val << (8 - (x % 8));

  // Draw left half
  old = frameBuffer[xCoord][y];
  frameBuffer[xCoord][y] = old ^ leftHalf;

  if(old & (old ^ frameBuffer[xCoord][y])) retVal = true;

  // Do not go offscreen
  if(x + 8 >= SCREEN_WIDTH) return retVal;

  // Draw right half
  old = frameBuffer[xCoord+1][y];
  frameBuffer[xCoord+1][y] = rightHalf;

  if(old & (old ^ frameBuffer[xCoord+1][y])) retVal = true;

  return retVal;

}