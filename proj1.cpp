/*****************************************
 ** File:    Proj1.cpp
 ** Project: CMSC 202 Project 1, Spring 2017
 ** Author:  Nima Roomi
 ** Date:    2/23/17
 ** Section: 12
 ** E-mail:  nimar1@gl.umbc.edu
 **
 ** This file contains all the code for playing Manhunt
 ** the first project of CMSC 202
 **
 ***********************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

//The board size constant
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 10;

int startMenu();
int mainMenu();
void loadMap(string fileName, int& investX, int& investY, int& targetX, int& targetY);
void newMap(int& investX, int& investY, int& targetX, int& targetY);
void printMenu(string map[BOARD_WIDTH][BOARD_HEIGHT], int& targetX, int& targetY);
void makeMove(string map[BOARD_WIDTH][BOARD_HEIGHT], string direction, int& investX, int& investY);
void hintMove(int investX, int investY, int targetX, int targetY);
bool checkWin(int investX, int investY, int targetX, int targetY);


int main(){
//  initilized variables for the users choices
    int userStartMenuChoice;
    int userMainMenuChoice;
    string fileName;
//  makes a 2d array 10 by 10 that holds strings
    string map[BOARD_WIDTH][BOARD_HEIGHT];
    
// the investigator and targets x and y coordinates
    int investX = 0;
    int investY = 0;
    int targetX = 0;
    int targetY = 0;
    
// prints the start menu and gets the users choice
    userStartMenuChoice = startMenu();

//  runs code based on the users start menu choice
    switch (userStartMenuChoice) {
        case 1:
            cout << "What is the name of the file?:" << endl;
            cin >> fileName;
            loadMap(fileName, investX, investY, targetX, targetY);
            
//          The for loop below makes the board
            for ( int i = 0; i < BOARD_HEIGHT; i++ ) {
                for ( int j = 0; j < BOARD_WIDTH; j++ ) {
                    map[i][j] = "_";
                }
            }
            
//          places the investigator and target on the map
            map[investX][investY] = "I";
            map[targetX][targetY] = "T";
            
            printMenu(map, targetX, targetY);
            
            break;
        case 2:
//          obtains the investigator and targets coords from user
            newMap(investX, investY, targetX, targetY);
            
//          The for loop below makes the board
            for ( int i = 0; i < BOARD_HEIGHT; i++ ) {
                for ( int j = 0; j < BOARD_WIDTH; j++ ) {
                    map[i][j] = "_";
                }
            }
            
//          places the investigator and target on the map
            map[investX][investY] = "I";
            map[targetX][targetY] = "T";
            
            printMenu(map,targetX,targetY);
            
            break;
        default:
//          prints text if the user decides to quit
            cout << "Giving up so soon?" << endl;
            cout << "Good-bye" << endl;
            break;
    }
    bool win = false;

//  if user has not decided to quit and no one has won code while statment will be true
    while(userStartMenuChoice != 3 and win == false){
//      prints main menu and gets users choice
        userMainMenuChoice = mainMenu();

        switch (userMainMenuChoice) {
            case 1:
                cout << "Searching North" <<endl;
                makeMove(map,"North", investX, investY);
                break;
            case 2:
                cout << "Searching East" << endl;
                makeMove(map,"East", investX, investY);
                break;
            case 3:
                cout << "Searching South" << endl;
                makeMove(map,"South", investX, investY);
                break;
            case 4:
                cout << "Searching West" << endl;
                makeMove(map,"West", investX, investY);
                break;
            case 5:
                cout << "Showing Map" << endl;
                printMenu(map, targetX , targetY);
                break;
            default:
//          prints text if the user decides to quit
                cout << "Giving up so soon?" << endl;
                cout << "Good-bye" << endl;
                userStartMenuChoice = 3;
                break;
        }
//      if statment checks if user has choosen to quit
        if(userStartMenuChoice !=3){
//          checks if there is a winner
            win = checkWin(investX, investY, targetX, targetY);
//          if no winner is found the game continues by giving hint and printing board
            if(!win){
                hintMove(investX, investY, targetX, targetY);
                printMenu(map, targetX, targetY);
            }else if (win){
//              winner is found will print ending text
                cout << "Congrats you found the target" << endl;
        }
        }
    }
    
    
}

//checks winner by compareing x and y values of investigator and target returns bool
bool checkWin(int investX, int investY, int targetX, int targetY){
    if (investX == targetX and investY == targetY){
        return true;
    }
    return false;
}

// gives users hint based on their location East or West first then North or South
void hintMove(int investX, int investY, int targetX, int targetY){
    if(investX < targetX){
        cout << "Try searching East" << endl;
    }
    else if (investX > targetX){
        cout << "Try searching West" << endl;
    }
    else if (investY > targetY){
        cout << "Try searching North" << endl;
    }
    else if (investY < targetY){
        cout << "Try searching South" << endl;
    }
    else if (investX == targetX and investY == targetY){
        cout << endl;
    }
}

// checks if users move is valid then moves the investigator if valid
void makeMove(string map[BOARD_WIDTH][BOARD_HEIGHT], string direction, int& investX, int& investY){
    if(direction == "North" and (investY-1 >= 0 and investY-1 <= 9)){
        map[investX][investY] = "*";
        map[investX][investY-1] = "I";
        investY -= 1;
    }
    if(direction == "East" and (investX+1 >= 0 and investX+1 <= 9)){
        map[investX][investY] = "*";
        map[investX+1][investY] = "I";
        investX += 1;
    }
    if(direction == "South" and (investY+1 >= 0 and investY+1 <= 9)){
        map[investX][investY] = "*";
        map[investX][investY+1] = "I";
        investY += 1;
    }
    if(direction == "West" and (investX-1 >= 0 and investX-1 <= 9)){
        map[investX][investY] = "*";
        map[investX-1][investY] = "I";
        investX -= 1;
    }
}

// takes the map array and prints it out to the user
void printMenu(string map[BOARD_WIDTH][BOARD_HEIGHT], int& targetX, int& targetY){
        for ( int i = 0; i < BOARD_HEIGHT; i++ ) {
            for ( int j = 0; j < BOARD_WIDTH; j++ ) {
                
                if(j == targetX and i == targetY){
                    cout << "_" << " ";
                }
                else{
                    cout << map[j][i] << " ";
                }
            }
        cout << endl;
        }
}

// takes in valid coordinates for investigator and target
void newMap(int& investX, int& investY, int& targetX, int& targetY){
    
    do{
        cout << "What is the X axis of the investigator?:" << endl;
        cin >> investX;
    } while(investX < 0 or investX > 9);
    
    do{
        cout << "What is the Y axis of the investigator?:" << endl;
        cin >> investY;
    } while(investY < 0 or investY > 9);
    
    do{
        cout << "What is the X axis of the target?:" << endl;
        cin >> targetX;
    } while(targetX < 0 or targetX > 9);
    
    do{
        cout << "What is the Y axis of the target?:" << endl;
        cin >> targetY;
    } while(targetY < 0 or targetY > 9);
}

// opens a save file of the users choice and loads investigators and targets coordinates
void loadMap(string fileName, int& investX, int& investY, int& targetX, int& targetY){
    
    ifstream inputStream;
    inputStream.open(fileName);
    
    inputStream >> investX >> investY >> targetX >> targetY;

}

// prints main menu and gets users choice as int checks if it is valid then returns it
int mainMenu(){
    
    int userChoice = 0;
    
    do{cout << "What would you like to do?" << endl;
    cout << "1. Search North" << endl;
    cout << "2. Search East" << endl;
    cout << "3. Search South" << endl;
    cout << "4. Search West" << endl;
    cout << "5. See Map" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter 1-6:" << endl;
    cin >> userChoice;
    } while(userChoice < 1 or userChoice > 6);
    
    return userChoice;
    
}

// prints start menu and gets users choice as int checks if it is valid then returns it
int startMenu(){
    int userChoice = 0;
    do{
        cout << "What would you like to do?" << endl;
        cout << "1. Load a simulation from file" << endl;
        cout << "2. Start a new simulation" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter 1 - 3:" << endl;
        cin >> userChoice;
    } while(userChoice < 1 or userChoice > 3);
    
    return userChoice;
}
