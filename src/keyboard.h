#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <string>

const string keymap = "x123qweasdzc4rfv";

unsigned char ch8_getch_blocking();
bool ch8_kbhit(char c);

#endif