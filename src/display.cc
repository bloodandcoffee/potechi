#include <string.h>
#include <iostream>
#include "display.h"

using namespace std;

void FrameBuffer::drawScreen() {

  cout << "--START OF FRAME--" << endl;

  // Dump frameBuffer to stdout
  // Temporary solution, replace with ncurses soon
  for(int i = 0; i < SCREEN_HEIGHT; i++) {
    for(int j = 0; j < SCREEN_WIDTH / 8; j++) {

      cout << ((frameBuffer[j][i] >> 7 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 6 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 5 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 4 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 3 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 2 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 1 & 0xF) ? "█" : " ");
      cout << ((frameBuffer[j][i] >> 0 & 0xF) ? "█" : " ");

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

  const unsigned char xCoord = x / 8;
  unsigned char old;

  // Draw left half
  const unsigned char offsetLeft = x % 8;

  old = frameBuffer[xCoord][y] >> offsetLeft;
  frameBuffer[xCoord][y] = old ^ val >> offsetLeft;

  if(old & (old ^ frameBuffer[xCoord][y])) retVal = true;


  // Do not go offscreen
  if(x + 8 >= SCREEN_WIDTH) {
    drawScreen();
    return retVal;
  }

  // Draw right half
  const unsigned char offsetRight = 16 - (x % 8);

  old = frameBuffer[xCoord+1][y] << offsetRight;
  frameBuffer[xCoord+1][y] = old ^ val << offsetRight;

  if(old & (old ^ frameBuffer[xCoord+1][y])) retVal = true;

  drawScreen();
  return retVal;

}