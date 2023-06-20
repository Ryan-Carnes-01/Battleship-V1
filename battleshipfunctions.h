#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;

//DEFAULTBOARD FUNCTIONS------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void defaultboard(bool board[10][10]){ //generates empty default board
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            board[i][j] = 0;
        }
    }

}
void defaulthitboard(int hitboard[10][10]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            hitboard[i][j] = 0;
        }
    }
}

//PRINT FUNCTIONS----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void printboard(bool board[10][10], int hitboard[10][10]){   //prints current board to user -- update to show hits based on hitboard
    int count = 0;
    cout << " 0  1  2  3  4  5  6  7  8  9 " << endl;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (board[i][j] == 0){
                cout << " ";
                if (hitboard[i][j] == 0){
                    cout << "~";
                }
                else{
                    cout << "O";
                }
                cout << " ";
            }
            if (board[i][j] == 1){
                cout << "[";
                if (hitboard[i][j] == 2){
                    cout << "X";
                }
                else{
                    cout << " ";
                } 
                cout << "]";
            }
            if (j == 9){
                cout << " " << count << " " <<endl;
                count++;
            }
        }
    }
    cout << endl;
}

void printhitboard(int hitboard[10][10]){
    int count = 0;
    cout << " 0  1  2  3  4  5  6  7  8  9 " << endl;
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if (hitboard[i][j] == 0){
                cout << " . ";
            }
            else if (hitboard[i][j] == 1){
                cout << " O ";
            }
            else if (hitboard[i][j] == 2){
                cout << " X ";
            }
            if (j == 9){
                cout << " " << count << " " <<endl;
                count++;
            }
        }
    }
    cout << endl;
}

void printgreeting(){
    cout << endl << "Welcome to BATTLESHIP" << endl << endl << "FIRST: Assemble your fleet" << endl << "SECOND: Engage the enemy fleet" << endl  << endl << "Press any key to continue..." << endl << endl;
    getch();
    cout << endl;
}

void printships(bool ships[5]){     //lists ships
    cout << "Which ship would you like to place? Enter the associated number" << endl;
    if (ships[0] == 1){
        cout << "1: " << left << setw(11) << "Destroyer " << "- size 2 [ ][ ]" << endl;
    }
    if (ships[1] == 1){
        cout << "2: " << left << setw(11) << "Submarine " << "- size 3 [ ] [ ] [ ]" << endl; 

    }
    if (ships[2] == 1){
        cout << "3: "<< left << setw(11) << "Cruiser " << "- size 3 [ ] [ ] [ ]" << endl;

    }
    if (ships[3] == 1){
        cout <<  "4: " << left << setw(11) << "Battleship " << "- size 4 [ ] [ ] [ ] [ ]" << endl; 

    }
    if (ships[4] == 1){
        cout <<  "5: " << left << setw(11) << "Carrier " << "- size 5 [ ] [ ] [ ] [ ] [ ]" << endl;
    }
    cout << endl;
}

void printvictory(){
    cout << "You Won!!!!! All enemy vessels scuttled or sunk!!!" << endl << endl;
    cout << "Press any key to end game...";
    getch();
}

void printdefeat(){
    cout << "You Lost!!!!! All friendly vessels scuttled or sunk!!!" << endl << endl;
    cout << "Press any key to end game...";
    getch();
}

//GET FUNCTIONS--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int getship(bool ships[5]){     //user puts in ship
    int shipnum;
reset:
    cin >> shipnum;
    shipnum -= 1;
    if (ships[shipnum] == 0){
        //error check, ship already used or outside scope
        cout << endl << "Invalid option, please pick again from the available ships" << endl << endl;
        goto reset;
    }
    ships[shipnum] = 0;
    return shipnum+1;
}

int getlength(int shipnum){     //get length of user inputted ship
    switch (shipnum){
        case 1:
            return 2;
            break;
        case 2:
            return 3;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        case 5:
            return 5;
            break;
        default:
            cout << "invalid shipnum" << endl;
            return 0;
            break;
    }
}

bool getrotation(){     //get rotation from user
    int choice;
rotatereset:
    cout << endl << "Pick an orientation:" << endl << "1:HORIZONTAL 2:VERTICAL" << endl << endl;
    cin >> choice;
    cout << endl;
    if(choice == 1){
        return 1;
    }
    else if(choice == 2){
        return 0;
    }
    else{
        cout << "invalid orientation, choose again" << endl;
        goto rotatereset;
    }
}

int getxcoord(int length, bool rotate){  //get/check x coords
    int xcoord;
xreset:
    cout << "Enter the initial x coordinate: ";
    cin >> xcoord;
    //check if in bounds
    if (xcoord > 9 || xcoord < 0){
        cout << "invalid x coordinate" << endl;
        goto xreset;
    }
    //check if length in bounds while horizontal
    if (rotate == 1){ 
        if (((xcoord + length-1) > 9) || ((xcoord + length-1) < 0)){
            cout << "Length exceeds board limit" << endl;
            goto xreset;
        }
    }
    return xcoord;
}

int getycoord(int length, bool rotate){   //get/check y coords
    int ycoord;
yreset:
    cout << "Enter the initial y coordinate: ";
    cin >> ycoord;
    cout << endl;
    //check if in bounds
    if (ycoord > 9 || ycoord < 0){
        cout << "invalid y coordinate" << endl;
        goto yreset;
    }
    //check if length in bounds while horizontal
    if (rotate == 0){ 
        if (((ycoord + length-1) > 9) || ((ycoord + length-1) < 0)){
            cout << "Length exceeds board limit" << endl;
            goto yreset;
        }
    }
    return ycoord;
}

//PLACESHIP FUNCTIONS---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool checkintersect(int x, int y, bool rotate, int length, bool board [10][10]){  //check if coords + rotation + length intersect an already present ship
    for (int i = 0; i < length; i++){
        if(rotate == 0){
            if(board[y+i][x] == 1){
                cout << "Intersects ship/Ship already present. Re-enter coords" << endl;
                return 1;
            }

        }
        if(rotate == 1){
            if(board[y][x+i] == 1){
                cout << "Intersects ship/Ship already present. Re-enter coords" << endl;
                return 1;
            }
        }
    }
    return 0;

}


void placeship(int x, int y, bool rotate, int length, bool board[10][10]){  //place ship on the board
    //place ship on [x][y], extending +length either right or down
    for (int i = 0; i < length; i++){
        if(rotate == 0){
            board[y+i][x] = 1;
        }
        if(rotate == 1){
            board[y][x + i] = 1;
        }
    }
};

//SHOOT FUNCTIONS------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int shootx(){ //get x to shoot
    int x;
shootxreset:
    cout << "Dial in x coordinate: ";
    cin >> x;
    //check if x between 0-9
    if (x > 9 || x < 0){
        cout << "Outside board, choose a valid coordinate"  << endl;
        goto shootxreset;
    }

    return x;
}

int shooty(){ //get y to shoot
    int y;
shootyreset:
    cout << "Dial in y coordinate: ";
    cin >> y;
    cout << endl;
    //check if y between 0-9
    if (y > 9 || y < 0){
        cout << "Outside board, choose a valid coordinate"  << endl;
        goto shootyreset;
    }

    return y;
}

bool shoot(int x, int y, bool board[10][10], int hitboard[10][10]){    //return true if hit then update board, false if miss
    if (board[y][x] == 1){ //if ship present
        if (hitboard[y][x] == 2){ //if already hit
            cout << "Ship already hit here" << endl;
            return 0; //return miss
        }
        else{
            hitboard[y][x] = 2; //update hit
            return 1; //return hit
        }
    }
    else{
        hitboard[y][x] = 1;
        return 0; //return miss
    }
}

//CPU FUNCTIONS-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void autoplaceships(bool cpuships[5], bool cpuboard[10][10]){
    srand((unsigned int)time(NULL));
    int shipnum;
    int length;
    int x;
    int y;
    bool rotate;
    for (int i = 0; i < 5; i++){
shipreset:
    //random choose ship
    shipnum = rand() % 5;
    //check if ship already used
    if (cpuships[shipnum] == 0){
        goto shipreset;
    }

    switch(shipnum){
        case 0:
            length = 2;
            break;
        case 1:
            length = 3;
            break;
        case 2:
            length = 3;
            break;
        case 3:
            length = 4;
            break;
        case 4:
            length = 5;
            break;
        default:
            cout << "invalid shipnum - error in autoplaceships" << endl;
            goto shipreset;
    }

    //random choose rotation
    rotate = rand() % 2; //1 = horiz 0 = vert

    //random choose x
    x = rand() % 10;
        //make sure +length inside bounds if horizontal
    if (rotate == 1){
        if(x + length > 9){
            goto shipreset;
        }
    }
    //random choose y
    y = rand() % 10;
        //make sure +length inside bounds if vertical
    if (rotate == 0){
        if(y + length > 9){
            goto shipreset;
        }
    }

    //check for present ships then place ships on cpuboard
    if (rotate == 0){
        for (int i = 0; i < length; i++){
            if (cpuboard [y+i][x] == 1){
                goto shipreset;
            }
        }
        for (int i = 0; i < length; i++){
            cpuboard[y+i][x] = 1;
        }
    }
    if (rotate == 1){
        for (int i = 0; i < length; i++){
            if(cpuboard [y][x+i] == 1){
                goto shipreset;
            }
        }
        for (int i = 0; i < length; i++){
            cpuboard[y][x+i] = 1;
        }
    }

    cpuships[shipnum] = 0;

    //loop until all ships placed
    }
}

bool cpushoot(bool board[10][10], int hitboard[10][10]){
    srand((unsigned int)time(NULL));
    int x;
    int y;
    x = rand() % 10;
    y = rand() % 10;

    //rand x
    //rand y

    //check if ship or if already hit
    if (board[y][x] == 1 && hitboard[y][x] != 2){
        hitboard[y][x] = 2;
        return true;
    }

    else{
        return false;
    }
    
}



//vector<bool> shotcounter; //(used to count hits/misses and when for the CPU)