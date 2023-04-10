//DEFAULTBOARD FUNCTIONS
void defaultboard(bool board[10][10]);
void defaulthitboard(int hitboard[10][10]);
//PRINT FUNCTIONS
void printboard(bool board[10][10], int hitboard[10][10]);
void printhitboard(int hitboard[10][10]);
void printgreeting();
void printships(bool ships[5]);
void printvictory();
void printdefeat();
//GET FUNCTIONS
int getship(bool ships[5]);
int getlength (int shipnum);
bool getrotation();
int getxcoord(int length, bool rotate, bool board[10][10]);
int getycoord(int length, bool rotate, bool board[10][10]);
//PLACESHIP FUNCTIONS
bool checkintersect(int x, int y, bool rotate, int length, bool board [10][10]);
void placeship(int x, int y, bool rotate, int length, bool board[10][10]);
//SHOOT FUNCTIONS
int shootx();
int shooty();
bool shoot(int x, int y, bool board[10][10], int hitboard[10][10]); //(true if hit, false if miss) (check if already hit)
//CPU FUNCTIONS
void autoplaceships(bool cpuships[5], bool cpuboard[10][10]);
bool cpushoot(bool board[10][10], int hitboard[10][10]);

