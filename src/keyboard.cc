#include <string>
#include <curses.h>
#include "keyboard.h"

using namespace std;

unsigned char ch8_getch_blocking() {

  timeout(-1);
  flushinp();

  int keyval = string::npos;

  while(true) {

    keyval = keymap.find(getch());
    if(keyval != string::npos) break;

  }

  timeout(0);
  return (unsigned char)keyval;

}

bool ch8_kbhit(char c) {

  

}