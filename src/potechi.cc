#include <iostream>
#include <chrono>
#include "system.h"

using namespace std;

int main(int argc, char** argv) {

  if(argc != 2) {
    cerr << "Please provide the path to the ROM file as the argument \n";
    return 1;
  }

  System potechi(argv[1]);

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

  return 0;

}