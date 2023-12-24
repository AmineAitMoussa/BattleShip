// creation d'un dépot GIT (github.com ou gitlab.com)
// vous envoyez l'url du dépot (url publique)
/**
 * @file main.c
 * @brief Main file for the Battleship Game.
 * @author AIT MOUSSA Amine
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"

/**
 * @brief Displays the title of the game.
 */
void title() {
    printf("===================================\n");
    printf("Battleship Game\n");
    printf("===================================\n");
}

/**
 * @brief Prints the main menu options.
 */
void printMenu() {
    printf("\n\n");
    printf("1. Start a Game\n");
    printf("2. Quit\n");
    printf("Choice : ");
}

/**
 * @brief Handles the player's choice from the main menu.
 */
void makechoice(){
    int choice;
    printMenu();
    while (scanf("%d", &choice)!=1){
        while(getchar()!='\n');
        printf("Invalid option. Please choose again.\n");
        printMenu();
    }
    if (choice == 1) {
        printf("Starting a game...\n");
        play();
    } 
    else if (choice == 2) {
        printf("Goodbye!\n");
    } 
    else {
        printf("Invalid option. Please choose again.\n");
        makechoice();
    }
}

/**
 * @brief Main function of the program.
 * @return 0 if the program executes successfully.
 */
int main() {
    title();
    makechoice();
    return 0;
}



