#include <iostream>
#include <chrono>
#include <ncurses.h>
#include "system.h"
#include "framebuffer.h"

using namespace std;

int main(int argc, char** argv) {

  if(argc != 2) {
    cerr << "Please provide the path to the ROM file as the argument \n";
    return 1;
  }

  // Set up ncurses
  initscr();
  resizeterm(SCREEN_HEIGHT + 2, SCREEN_WIDTH*2 + 2);

  for(int i = 0; i < SCREEN_WIDTH*2 + 2; i++) {
    mvaddch(0, i, (char)219);
    mvaddch(SCREEN_HEIGHT + 1, i, (char)219);
  }

  for(int i = 0; i < SCREEN_HEIGHT + 2; i++) {
    mvaddch(i, 0, (char)219);
    mvaddch(i, SCREEN_WIDTH*2 + 1, (char)219);
  }

  refresh();
  
  // Set up emulator
  System potechi(argv[1]);


  // Fetch-decode-execute loop
  chrono::duration<double, std::ratio<1, 60>> lastTime(chrono::system_clock::now().time_since_epoch());

  while(true) {

    chrono::duration<double, std::ratio<1, 60>> now(chrono::system_clock::now().time_since_epoch());

    if((now - lastTime).count() >= 1) {
      potechi.delay--;
      potechi.sound--;

      lastTime = now;
    }

    potechi.fetchExecute();

  }

  endwin();

  return 0;

}