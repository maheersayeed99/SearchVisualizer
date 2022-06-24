#include "maze.h"

int WIDTH = 1250;   // Define width and height of window
int HEIGHT = 500;


// Only input is rows
int main(int argc, char* argv[]){

    srand(time(NULL));          // Start time seeding

    int input = 25;             // Set default as 20 rows, 40 columns
    if(argc>1)
        input = atoi(argv[1]);

    ApplicationMain App(input,input,WIDTH,HEIGHT);

    while(!App.terminate()){
        App.run();
        App.draw();
    }

    return 0;
}