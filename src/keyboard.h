#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <string>

const std::string keymap = "x123qweasdzc4rfv";

// c is the CHIP-8 virtual keyboard key to check for (0x0-0xF)
bool ch8_keypressed(unsigned char c);
unsigned char ch8_getch_blocking();

#endif
