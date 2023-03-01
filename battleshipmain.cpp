#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include "battleshipfunctions.h"

using namespace std;

//adding functionality/support for play vs cpu. Ship autoplace done, CPU shooting phase algorithm WIP 

int main(){

//variables
bool p1board[10][10];
int p1hitboard[10][10]; //(used to track/display p1hits)
bool cpuboard[10][10];
int cpuhitboard[10][10];

bool p1ships[5] = {1, 1, 1, 1, 1};
bool cpuships[5] = {1, 1, 1, 1, 1};
int shipnum;
int length;
bool rotate;
int x;
int y;
int p1hits = 0; //at 17 p1hits, all cpuships sank = WIN
int cpuhits = 0;

defaultboard(p1board); //generate empty p1board
defaulthitboard(p1hitboard);
defaultboard(cpuboard);
defaulthitboard(cpuhitboard);
printgreeting();


    for (int i = 0; i < 5; i++){  //until all p1ships are chosen
        printboard(p1board, p1hitboard);
        printships(p1ships);        //list p1ships, user chooses one
        shipnum = getship(p1ships);   //use shipnum to get length
        length = getlength(shipnum); //get length
        rotate = getrotation();        //get rotation
    coordreset:                         //reset if ship intersects
        x = getxcoord(length, rotate, p1board);  //get/check coords 
        y = getycoord(length, rotate, p1board);

        if (checkintersect(x, y, rotate, length, p1board)){
            goto coordreset;
        }

        placeship(x, y, rotate, length, p1board); //place the ship once all error checks are passed  
    }

    //CPU places cpuships randomly
    
    autoplaceships(cpuships, cpuboard);
    
    


while(p1hits != 17){  //until all cpuships sunk
  printhitboard(cpuhitboard);
  printboard(p1board, p1hitboard);
  cout << "Fire your artillery!" << endl;
  x = shootx(); //get x coord for shot
  y = shooty(); //get y coord for shot
  if(shoot(x, y, cpuboard, cpuhitboard) == true){
    p1hits++;
    cout << "Hit!" << endl << endl; //increment p1hits if hit
  }
  else{
    cout << "Miss!" << endl << endl; //loop again if miss
  }

  //CPU takes shot back randomly - unless win condition reached 
  if(cpushoot(p1board, p1hitboard)){
    cpuhits++;
    cout << "Taking fire!" << endl << endl;
  }
  else{
    cout << "The enemy misses!" << endl << endl;
  }
  if (cpuhits == 17){
    printdefeat();
    return 0;
  }

}

printvictory();


return 0; 
}