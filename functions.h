#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

#define NB_SHIPS 5
#define SIZE 10

enum Case {
    WATER,        
    WATER_SHOT,   
    BOAT, 
    WRECK         
};
typedef struct{
    enum Case** board;
    int size;
} Gameboard;
typedef struct{
    int x;
    int y;
}Point;
typedef struct{
    int size ;
    Point position;
    Point orientation; //(1,0) : Vertical or (0,1) : Horizontal
} Ship;
typedef struct{
    Gameboard* playerBoard;
    Gameboard* botBoard;
    Ship* playerships;
    Ship* botships;
}Game;




Gameboard* createboard();
Ship createship();
int isshipalive(Ship* ship, Gameboard* board);
void placeships(Game* game);
Game creategame();
void displayBoard(enum Case** board, int who);
void playerturn(Gameboard* gameboard);
void botturn(Gameboard* gameboard);
void freeGame(Game* game);
void freeBoard(Gameboard* board);
void play();





#endif