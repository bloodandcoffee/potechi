#include <string.h>
#include <iostream>
#include "display.h"

using namespace std;

// Debugging implementation
void FrameBuffer::drawScreen() {

  cout << "--START OF FRAME--" << endl;

  // Dump frameBuffer to stdout
  // Temporary solution, replace with ncurses soon
  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    for(int j = 0; j < SCREEN_WIDTH / 8; j++) {

      cout << ((frameBuffer[j][i] >> 7 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 6 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 5 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 4 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 3 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 2 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 1 & 0x1) ? "██" : "  ");
      cout << ((frameBuffer[j][i] >> 0 & 0x1) ? "██" : "  ");

    }

    cout << "\n";
  }

  cout << "--END OF FRAME--" << endl;
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