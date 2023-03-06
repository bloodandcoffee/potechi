#ifndef DISPLAY_H
#define DISPLAY_H

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

class FrameBuffer {

  unsigned char frameBuffer[SCREEN_WIDTH / 8][SCREEN_HEIGHT];

  void drawScreen();

  public:
  void clearScreen();
  bool setByte(unsigned char x, unsigned char y, unsigned char val);

};

#endif