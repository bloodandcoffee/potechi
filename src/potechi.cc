#include <iostream>
#include "system.h"

using namespace std;

int main(int argc, char** argv) {

  if(argc != 2) {
    cerr << "Please provide the path to the ROM file as the argument \n";
    return 1;
  }

  System potechi;
  potechi.loadProgram(argv[1]);

  while(true) {
    potechi.fetchExecute();
  }

  return 0;

}