#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <time.h>

using namespace std;

char myCar[4][4] = //-------My Car 2D Array
    {
        {' ', '#', '#', ' '},
        {'#', '#', '#', '#'},
        {' ', '#', '#', ' '},
        {'#', '#', '#', '#'}
    };

char enemyCar[4][4] = //-------Enemy Car 2D Array
    {
        {'*', '*', '*', '*'},
        {' ', '*', '*', ' '},
        {'*', '*', '*', '*'},
        {' ', '*', '*', ' '}
    };

char Maze[43][101]; //--------Game maze

//----------------------------Function prototype Start------------------------ 

void header(); //--------------function for simple Header
string mainMenu(); //---------------function game's main menu
void moveCar(int x, int y, int m); //---------------------function for move car
void addCover(int x, int y, int m); //--------------------function for removing spaces leaved by car
void gotoxy(int x, int y); //--------------------function for displaying something on specific location
int genRanNum(); //--------------------function for genertaing random number 
void genEnemyIdx(); //--------------------function for genertaing enemy cars indexes
void printCar(int idx); //--------------------function for displaying car
void moveEnemyCar(); //--------------------function for moving enemy car
void printMaze(); //--------------------function for displaying game maze
void playGame(int carX, int carY,int speed, int m); //--------------------function for play game
void resetEnemyCar(); //--------------------function for reseting enemy car index 
void removingCar(int idx); //--------------------function for removing enemy cars
void printScore(); //--------------------function for displaying score on screen
void printLives(); //--------------------function for displayiing lives on screen
bool collision(int x, int y); //--------------------function for  the checking the collision of the cars
void gameOver(); //--------------------function for  game over condition
void loadMaze();  //--------------------function for  loading game maze from file
void storeData(); //--------------------function for  storing data into file
void printHighScore(); //--------------------function for  displaying high score
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // for using colors 


int enemyX[6]; // enemy x-axis array
int enemyY[6]; // enemy y-axis array
bool enemyFlag[6] = {0, 0, 0, 0, 0, 0};  // enemy flags array
int score = 0; // variable for score
int highScore; // variable for high score
int lives = 3; // variable for lives
int countLoop = 0;  // variable for loop count

// -------------------------- main function
main()
{
    int carX = 34; // my car x-axis
    int carY = 35; // my car y-axis
    int m = 0; // variable for storing direction of my car
    system("cls");
    loadMaze(); // loading maze from file
    string option = " "; // variable for option
    while(true) //----------------- menu loop
    {
        system("cls");
        option = "0"; // for option
        option = mainMenu(); // main menu
        if(option == "1") // for option 1
        {
            lives = 3; // making lives 3
            score = 0; // making score zero
            // making enemy flag 0
            enemyFlag[0] = 0;
            enemyFlag[1] = 0;
            enemyFlag[2] = 0;
            enemyFlag[3] = 0;
            enemyFlag[4] = 0;
            enemyFlag[5] = 0;
            system("cls");
            printMaze(); // for printing maze
            printMaze(); // for printing maze
            while (true) // ---------------------game loop
            {
                Sleep(10); // delaying 
                if (GetAsyncKeyState(VK_LEFT)) // for moving left
                {
                    if (carX >= 16) // cannot move left if coloumn is less than 16
                    {
                        carX--; // subtracting 1
                        m = 1; // giving direction
                    }
                }
                if (GetAsyncKeyState(VK_RIGHT)) // for moving right
                {
                    if (carX <= 51) // cannot move right if coloumn is more than 51
                    {
                        carX++; // adding 1
                        m = 2; // giving direction
                    }
                }
                if (GetAsyncKeyState(VK_ESCAPE)) // for exit from game
                {
                    score = 0; // making score zero 
                    lives = 3; // making lives 3 
                    break; // game loop break;
                }
                moveCar(carX, carY, m); // moving my car
                if (countLoop == 5) // genrating enemy car after 5 loop count
                {
                    genEnemyIdx(); // generating enemy car
                    countLoop = 0; // making count loop 0
                }
                printCar(0); // printing enemy car 1
                printCar(1); // printing enemy car 2
                printCar(2); // printing enemy car 3
                printCar(3); // printing enemy car 4
                printCar(4); // printing enemy car 5
                printCar(5); // printing enemy car 6
                moveEnemyCar(); // moving enemy cars
                resetEnemyCar(); // reseting enenmy cars indexes
                printScore(); // printing score on screen
                printHighScore(); // printing high score
                printLives(); // printin glives of user car
                if(collision(carX, carY)) // checking colliosions of the cars
                {
                    lives--; // decreasing live by 1
                    carX = 34; // my car x axis 
                    carY = 35; // my car y-axis
                    addCover(carX, carY, m); // removing garbage leaved by my acr
                    getch();
                }
                if(lives == 0) // if lives is zero
                {
                    if(score > highScore) // if score greater than high score
                    {
                        highScore = score; // giving high score value
                        storeData(); // storing high score into file
                    }
                    gameOver(); // displaying game over
                    break; // break game loop
                }
                countLoop++; // adding in loop count
            }
        }
        else if(option == "2") // for option 2
        {
            system("cls");
            header(); // game header
            cout << "\t\t\t\t\t\t Game menu > Help!" <<endl;
            cout << "\t\t\t\t\t\t -----------------" <<endl; 
            cout << "\t\t\t\t\t\t Controls" <<endl;
            cout << "\t\t\t\t\t\t --------" <<endl;
            cout << "\t\t\t\t\t\t Left key for LEFT" <<endl;
            cout << "\t\t\t\t\t\t Right key for right" <<endl;
            cout <<endl;
            cout << "\t\t\t\t\t\t Rules" <<endl;
            cout << "\t\t\t\t\t\t -----" <<endl;
            cout << "\t\t\t\t\t\t You can only move left & right" <<endl;
            cout << "\t\t\t\t\t\t You have to save your car from collision" <<endl;
            cout << "\t\t\t\t\t\t With Each car pass by you, you get one score" <<endl;
            cout << "\t\t\t\t\t\t On every collision, one live lose" <<endl;
            cout << "\t\t\t\t\t\t Press any key to continue" <<endl;
            getch();
        }
        else if(option == "3") // for option 3
        {
            break; // breaking menu loop
        }
        else // for invalid input
        {
            SetConsoleTextAttribute(h,4); //----This function is for colouring the text
            cout << "\t\t\t\t\t\t Invalid Input" <<endl; //------ invalid message
            cout << "\t\t\t\t\t\t Press any key to continue...";
            getch();
            SetConsoleTextAttribute(h,15); //----This function is for colouring the text
            system("cls");
            continue;         
        }
    }
}

// function implementation for moving car
void moveCar(int carX, int carY, int m)
{
    int n = carY; // giving n value of cary-axis
    addCover(carX, carY, m); // removing garbage 
    SetConsoleTextAttribute(h, 6); ;  //----This function is for colouring the text
    for (int i = 0; i < 4; i++) 
    {
        gotoxy(carX, n);
        for (int j = 0; j < 4; j++)
        {
            cout << myCar[i][j]; // printing my car
        }
        n++;
    }
    SetConsoleTextAttribute(h, 15);;  //----This function is for colouring the text
    addCover(carX, carY, m); // removing garbage
}

// function implementation for removing garbage leaved by our car
void addCover(int x, int y, int m)
{
    if (m == 1) // if car moves left
    {
        x = x + 4;
        for (int t = 0; t < 4; t++) // adding spaces on right side
        {
            gotoxy(x, y + t);
            cout << " ";
        }
    }
    else if (m == 2) // if car moves right
    {
        x--;
        for (int t = 0; t < 4; t++) // adding spaces on left side
        {
            gotoxy(x, y + t);
            cout << " ";
        }
    }
}

// function implementation for displaying something on specific location
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

// function implementation for generating random numbers
int genRanNum()
{
    return rand() % 6; // from 0 to 6 random number
}

// function implementation for generating random enemy indexes
void genEnemyIdx()
{
    int num;
    num = genRanNum(); // generating random number
    if (num == 0 && enemyFlag[0] == 0) // for random num = 0 and enemy flag off
    {
        enemyX[0] = 16; // enemy car[0] x index 
        enemyY[0] = 1; // enemy car[0] y index
        enemyFlag[0] = 1; // to make enemy flag again on 
    }
    if (num == 1 && enemyFlag[1] == 0) // for random num = 1 and enemy flag off
    {
        enemyX[1] = 23; // enemy car x[1] index
        enemyY[1] = 1; // enemy car y[1] index
        enemyFlag[1] = 1; // to make enemy flag again on
    }
    if (num == 2 && enemyFlag[2] == 0) // for random num = 2 and enemy flag off
    {
        enemyX[2] = 30; // enemy car[2] x index
        enemyY[2] = 1; // enemy car[2] x index
        enemyFlag[2] = 1; // to make enemy flag again on
    }
    if (num == 3 && enemyFlag[3] == 0) // for random num = 3 and enemy flag off
    {
        enemyX[3] = 37; // enemy car[3] x index
        enemyY[3] = 1; // enemy car[3] x index
        enemyFlag[3] = 1; // to make enemy flag again on
    }
    if (num == 4 && enemyFlag[4] == 0) // for random num = 4 and enemy flag off
    {
        enemyX[4] = 44; // enemy car[4] x index
        enemyY[4] = 1; // enemy car[4] x index
        enemyFlag[4] = 1; // to make enemy flag again on
    }
    if (num == 5 && enemyFlag[5] == 0) // for random num = 5 and enemy flag off
    {
        enemyX[5] = 51; // enemy car[5] x index
        enemyY[5] = 1; // enemy car[5] x index
        enemyFlag[5] = 1; // to make enemy flag again on
    }
}
// function implementation for printing enemy car
void printCar(int idx)
{
    if (enemyFlag[idx] == 1) // print car if enemy flag is on in idx
    {
        SetConsoleTextAttribute(h, 4); // for coloring text 
        for (int i = 0; i < 4; i++)
        {
            gotoxy(enemyX[idx], enemyY[idx] + i); // to print data on a particular decision
            for (int j = 0; j < 4; j++)
            {
                cout << enemyCar[i][j];
            }
        }
        SetConsoleTextAttribute(h, 15); // for coloring text
    }
}
// function implementation for move enemy car
void moveEnemyCar()
{
    for (int i = 0; i < 6; i++)
    {
        if (enemyFlag[i] == 1) // if enemy flag is ON than the game will be print
        {
            gotoxy(enemyX[i], enemyY[i] - 1); // to print data on a particular location on console
            cout << "    "; // to print spaces 
            enemyY[i]++; // y index increased by one every time
        }
    }
}
// function implemetation for print game maze or map
void printMaze()
{
    for (int i = 0; i < 43; i++) // loop for printing rows of the maze
    {
        gotoxy(0, i); // for print data on a particular location on console
        for (int j = 0; j < 101; j++) // loop for printing coloumns of the maze
        {
            cout << Maze[i][j];
        }
        cout << endl; // for the next line
    }
}
// function implementation for reset car
void resetEnemyCar()
{
    for (int i = 0; i < 6; i++) // loop for enemy car reset purpose
    {
        if (enemyY[i] == 37) // if enemy y index is 37 or if enemy car is out of the maze
        {
            removingCar(i); // function call for removing those enemy cars whose index is 27
            enemyY[i] = 0; // y index of the car become 0
            enemyFlag[i] = 0; // enemy flag is also zero
            score++; // score is increased by one if enemy car is passed by our car
        }
    }
}
// function implementation for removing enemy car
void removingCar(int idx)
{
    for (int i = 0; i < 6; i++) // loop for every enemy car 
    {
        gotoxy(enemyX[idx], enemyY[idx] - i); // for print data on a particular location on console
        cout << "    ";
        gotoxy(enemyX[idx], enemyY[idx] + i); // for print data on a particular location on console
        cout << "    ";
    } 
}
// function implementation for print scores
void printScore()
{
    gotoxy(72, 17); // for print data on a particular location on console
    cout << "Score : " << score;
}
// function implementation for print lives on the screen
void printLives()
{
    gotoxy(72, 21); // for print data on a particular location on console
    cout << "Lives : " << lives;
}
// function implentation for game over statement
void gameOver()
{
    gotoxy(80,24); // for print data on a particular location on console
    cout << "GAME OVER!";
}
// function implementation for print high score
void printHighScore()
{
    gotoxy(72,15); // for print data on a particular location on console
    cout << "High Score : " << highScore;
}
// function implementation for collision
bool collision(int x, int y)
{
    for (int i = 0; i < 6; i++) // loop for the checking collision of every enemy car with our car
    {
        if (x == enemyX[i] && y == enemyY[i] + 3)// if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        if (x == enemyX[i] + 1 && y == enemyY[i] + 3) // if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        if (x == enemyX[i] + 2 && y == enemyY[i] + 3) // if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        if (x == enemyX[i] + 3 && y == enemyY[i] + 3) // if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        if (x + 3 == enemyX[i] + 1 && y == enemyY[i] + 3) // if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        if (x + 3 == enemyX[i] + 2 && y == enemyY[i] + 3) // if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        if (x + 3 == enemyX[i] + 3 && y == enemyY[i] + 3) // if coordinates of our car and enemy car is equal than return true
        {
            return true;
        }
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
            {
                if(x == enemyX[i] + 3 && y + j == enemyY[i] + k) // if coordinates of our car and enemy car is equal than return true
                {
                    return true;
                }
                if(x + 3 == enemyX[i] && y + j == enemyY[i] + k) // if coordinates of our car and enemy car is equal than return true
                {
                    return true;
                }
            }
        }
    }
    return false; // if coordinates of our car and enemy car is equal not than return true
}
// function implementation for header of the program
void header()
{
    cout << "\t\t\t\t\t\t ------------------------------------------------------" <<endl;
    cout << "\t\t\t\t\t\t|                    Car Racing Game                   |" <<endl;
    cout << "\t\t\t\t\t\t ------------------------------------------------------" <<endl;
    cout <<endl;
    cout <<endl;
}
// function implementation for game main menu
string mainMenu()
{
    header();
    cout << "\t\t\t\t\t\t Game Menu" <<endl;
    cout << "\t\t\t\t\t\t ---------" <<endl;
    cout << "\t\t\t\t\t\t 1. Play Game" <<endl;
    cout << "\t\t\t\t\t\t 2. Help" <<endl;
    cout << "\t\t\t\t\t\t 3. Exit" <<endl;
    cout << "\t\t\t\t\t\t Your Option...";
    string option;
    cin >> option;
    return option; // for return option
}
// function implementaion for load maze
void loadMaze()
{
    string maze; // for temporary store data from file
    fstream file; // declare file variable
    file.open("Track.txt", ios::in); // read data from file
    for (int i = 0; i < 43; i++) // loop for the row of maze
    {
        getline(file, maze); // getline is used for getting info with spaces
        for (int j = 0; j < 101; j++) // loop for the coloumn of maze
        {
            Maze[i][j] = maze[j]; // for store data into the 2D array of maze
        }
    }
    file.close(); // for closing maze

    fstream file1; // declare file variable
    file1.open("highScore.txt", ios::in); // read data from file
    file1 >> highScore; // get data into the global variable from file
    file1.close(); // for closing file
}

void storeData()
{
    fstream file1;  // declare file variable
    file1.open("highScore.txt", ios::out); // write data from file
    file1 << highScore; // store data from variable to file
    file1.close(); // for closing file
}