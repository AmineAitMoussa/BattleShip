#include "functions.h"

/**
 * @brief Creates a new game board.
 * @return A pointer to the created Gameboard structure.
 */
Gameboard* createboard(){
    Gameboard* gameboard = NULL;

    // Allocate memory for the Gameboard structure
    gameboard = malloc(sizeof(Gameboard));
    if(gameboard == NULL){
        printf("\nMemory allocation error\n");
        exit(1);
    }

    // Set the size of the game board
    gameboard->size = SIZE;

    // Allocate memory for the rows of the game board
    gameboard->board = malloc(gameboard->size * sizeof(enum Case*));
    if(gameboard->board == NULL){
        printf("\nMemory allocation error\n");
        exit(1);
    }

    // Allocate memory for each column in every row
    for (int i = 0; i < SIZE; ++i) {
        gameboard->board[i] = malloc(gameboard->size * sizeof(enum Case));
        if(gameboard->board[i] == NULL){
            printf("\nMemory allocation error\n");
            exit(1);
        }
    }

    // Initialize each cell of the game board to WATER
    for (int i = 0; i < gameboard->size; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            gameboard->board[i][j] = WATER;
        }
    }

    return gameboard;
}

/**
 * @brief Creates a new ship with a random orientation and position.
 * @return The created Ship structure.
 */
Ship createship(){
    srand(time(NULL));

    Ship ship;
    ship.size = 3;

    // Randomly choose the orientation of the ship
    if(rand() % 2 == 0){
        ship.orientation.x = 1;
        ship.orientation.y = 0;
    } 
    else{
        ship.orientation.x = 0;
        ship.orientation.y = 1;
    }

    // Initialize the position to (-1, -1)
    ship.position.x = -1;
    ship.position.y = -1;

    return ship;
}


/**
 * @brief Checks if a ship is still alive based on its position and orientation on the game board.
 * @param ship Pointer to the Ship structure.
 * @param board Pointer to the Gameboard structure.
 * @return 0 if the ship is wrecked, 1 if it is still alive.
 */
int isshipalive(Ship* ship, Gameboard* board) {
    // Check if all three consecutive positions of the ship are WRECK
    if (board->board[ship->position.x][ship->position.y] == WRECK &&
        board->board[ship->position.x + ship->orientation.x][ship->position.y + ship->orientation.y] == WRECK &&
        board->board[ship->position.x + 2 * ship->orientation.x][ship->position.y + 2 * ship->orientation.y] == WRECK) {
        return 0; // The ship is wrecked
    }

    return 1; // The ship is still alive
}


/**
 * @brief Randomly places ships on the game boards for both the player and the bot.
 * @param game Pointer to the Game structure.
 */
void placeships(Game* game) {
    for (int i = 0; i < NB_SHIPS; i++) {
        do {
            srand(time(NULL)); // Move srand outside the loop to avoid generating the same random numbers
            // Randomly assign positions for player and bot ships
            game->playerships[i].position.x = rand() % 10;
            game->playerships[i].position.y = rand() % 10;
            game->botships[i].position.x = rand() % 10;
            game->botships[i].position.y = rand() % 10;
        } while (
            // Check if positions are within the board limits and if there is any overlap with existing boats
            game->playerships[i].position.x >= 10 ||
            game->playerships[i].position.y >= 10 ||
            game->playerships[i].position.x + game->playerships[i].orientation.x >= 10 ||
            game->playerships[i].position.y + game->playerships[i].orientation.y >= 10 ||
            game->playerships[i].position.x + 2 * game->playerships[i].orientation.x >= 10 ||
            game->playerships[i].position.y + 2 * game->playerships[i].orientation.y >= 10 ||
            game->botships[i].position.x >= 10 ||
            game->botships[i].position.y >= 10 ||
            game->botships[i].position.x + game->botships[i].orientation.x >= 10 ||
            game->botships[i].position.y + game->botships[i].orientation.y >= 10 ||
            game->botships[i].position.x + 2 * game->botships[i].orientation.x >= 10 ||
            game->botships[i].position.y + 2 * game->botships[i].orientation.y >= 10 ||
            game->playerBoard->board[game->playerships[i].position.x][game->playerships[i].position.y] == BOAT ||
            game->playerBoard->board[game->playerships[i].position.x + game->playerships[i].orientation.x][game->playerships[i].position.y + game->playerships[i].orientation.y] == BOAT ||
            game->playerBoard->board[game->playerships[i].position.x + 2 * game->playerships[i].orientation.x][game->playerships[i].position.y + 2 * game->playerships[i].orientation.y] == BOAT ||
            game->botBoard->board[game->botships[i].position.x][game->botships[i].position.y] == BOAT ||
            game->botBoard->board[game->botships[i].position.x + game->botships[i].orientation.x][game->botships[i].position.y + game->botships[i].orientation.y] == BOAT ||
            game->botBoard->board[game->botships[i].position.x + 2 * game->botships[i].orientation.x][game->botships[i].position.y + 2 * game->botships[i].orientation.y] == BOAT
        );

        // Mark player and bot ship positions on their respective boards
        game->playerBoard->board[game->playerships[i].position.x][game->playerships[i].position.y] = BOAT;
        game->playerBoard->board[game->playerships[i].position.x + game->playerships[i].orientation.x][game->playerships[i].position.y + game->playerships[i].orientation.y] = BOAT;
        game->playerBoard->board[game->playerships[i].position.x + 2 * game->playerships[i].orientation.x][game->playerships[i].position.y + 2 * game->playerships[i].orientation.y] = BOAT;

        game->botBoard->board[game->botships[i].position.x][game->botships[i].position.y] = BOAT;
        game->botBoard->board[game->botships[i].position.x + game->botships[i].orientation.x][game->botships[i].position.y + game->botships[i].orientation.y] = BOAT;
        game->botBoard->board[game->botships[i].position.x + 2 * game->botships[i].orientation.x][game->botships[i].position.y + 2 * game->botships[i].orientation.y] = BOAT;
    }
}


/**
 * @brief Creates a new game with initialized game boards, ships, and ship placements.
 * @return The initialized Game structure.
 */
Game creategame() {
    Game game;

    // Create player and bot game boards
    game.playerBoard = createboard();
    game.botBoard = createboard();

    // Allocate memory for player ships
    game.playerships = malloc(NB_SHIPS * sizeof(Ship));
    if (game.playerships == NULL) {
        printf("\nMemory allocation error\n");
        exit(1);
    }

    // Allocate memory for bot ships
    game.botships = malloc(NB_SHIPS * sizeof(Ship));
    if (game.botships == NULL) {
        printf("\nMemory allocation error\n");
        exit(1);
    }

    // Initialize player and bot ships and place them on the boards
    for (int i = 0; i < NB_SHIPS; i++) {
        game.playerships[i] = createship();
        game.botships[i] = createship();
    }

    // Randomly place ships on player and bot boards
    placeships(&game);

    return game;
}


/**
 * @brief Displays the game board.
 * 
 * @param board The game board to be displayed.
 * @param who An indicator (0 for player, 1 for the opponent, here the bot).
 */
void displayBoard(enum Case** board, int who) {
    if (who == 0) {
        // Display player's own board
        printf("    ");
        for (char col = 'A'; col < 'A' + SIZE; ++col) {
            printf(" %c ", col);
        }
        printf("\n\n");
        for (int row = 0; row < SIZE; ++row) {
            printf("%2d| ", 1 + row);
            for (int col = 0; col < SIZE; ++col) {
                switch (board[row][col]) {
                    case WATER:
                        printf(" ~ ");
                        break;
                    case WATER_SHOT:
                        printf(" v ");
                        break;
                    case BOAT:
                        printf(" O ");
                        break;
                    case WRECK:
                        printf(" X ");
                        break;
                    default:
                        printf(" ? ");
                }
            }
            printf("\n");
        }
    } else {
        // Display bot's board (only show water shots and wrecks)
        printf("    ");
        for (char col = 'A'; col < 'A' + SIZE; ++col) {
            printf(" %c ", col);
        }
        printf("\n\n");
        for (int row = 0; row < SIZE; ++row) {
            printf("%2d| ", 1 + row);
            for (int col = 0; col < SIZE; ++col) {
                switch (board[row][col]) {
                    case WATER_SHOT:
                        printf(" ~ ");
                        break;
                    case WRECK:
                        printf(" X ");
                        break;
                    default:
                        printf(" ? ");
                }
            }
            printf("\n");
        }
    }
}


/**
 * @brief Handles a player's turn to make a shot.
 * 
 * @param gameboard The player's game board.
 */
void playerturn(Gameboard* gameboard) {
    char col;
    int line, column;

    // Clear input buffer
    while (getchar() != '\n');

    printf("Next shot (ex: B5): ");
    
    // Validate and process user input
    while (scanf("%c%d", &col, &line) != 2 || line < 1 || line > SIZE || col < 'A' || col > 'A' + SIZE) {
        printf("\nInvalid option. Please choose again.\n");
        printf("\nNext shot (ex: B5): ");
        
        // Clear input buffer
        while (getchar() != '\n');
    }

    column = col - 'A';

    // Process the shot result
    if (gameboard->board[line - 1][column] == WATER) {
        printf("Right in the water!\n");
        gameboard->board[line - 1][column] = WATER_SHOT;
    } else if (gameboard->board[line - 1][column] == BOAT) {
        printf("A boat got hit!\n");
        gameboard->board[line - 1][column] = WRECK;
    } else {
        printf("Already shot here. Choose another case.\n");
        playerturn(gameboard);
    }
}


/**
 * @brief Handles the bot's turn to make a shot.
 * 
 * @param gameboard The opponent's game board.
 */
void botturn(Gameboard* gameboard) {
    int line, column;

    // Generate random shot coordinates
    srand(time(NULL));
    line = rand() % SIZE;
    column = rand() % SIZE;

    // Process the shot result
    if (gameboard->board[line][column] == WATER) {
        printf("Plouf!\n");
        gameboard->board[line][column] = WATER_SHOT;
    } else if (gameboard->board[line][column] == BOAT) {
        printf("One of your boats got hit!\n");
        gameboard->board[line][column] = WRECK;
    } else {
        printf("Plouf!\n");
    }
}


/**
 * @brief Frees the memory allocated for a game board.
 * 
 * @param board The game board to be freed.
 */
void freeBoard(Gameboard* board) {
    for (int i = 0; i < SIZE; ++i) {
        free(board->board[i]);
    }
    free(board->board);
    free(board);
}

/**
 * @brief Frees the memory allocated for an array of ships.
 * 
 * @param ships The array of ships to be freed.
 */
void freeship(Ship* ships) {
    free(ships);
}

/**
 * @brief Frees the memory allocated for a game.
 * 
 * @param game The game to be freed.
 */
void freeGame(Game* game) {
    freeBoard(game->playerBoard);
    freeBoard(game->botBoard);
    freeship(game->playerships);
    freeship(game->botships);
    free(game);
}


/**
 * @brief Initiates and executes the Battleship game.
 */
void play() {
    int turn = 0, lp, lb;
    printf("\nStart of the game! Please wait during the creation of the boards...\n");

    Game game = creategame();

    while (lb != 0 && lp != 0) {
        lb = 0;
        lp = 0;
        if (turn % 2 == 0) {
            printf("\nYour turn to play\n");
            printf("\nView of the enemy field:\n");
            displayBoard(game.botBoard->board, 1);
            playerturn(game.botBoard);
            displayBoard(game.botBoard->board, 1);
        } else {
            printf("\nBot's turn\n");
            botturn(game.playerBoard);
            printf("\nView of your field:\n");
            displayBoard(game.playerBoard->board, 0);
        }
        turn = turn + 1;
        for (int i = 0; i < NB_SHIPS; i++) {
            lp = lp + isshipalive(&(game.playerships[i]), game.playerBoard);
            lb = lb + isshipalive(&(game.botships[i]), game.botBoard);
        }
    }

    if (lb == 0) {
        printf("You won!\n");
        printf("End of the party!\n");
    } else {
        printf("The bot won!\n");
        printf("End of the party!\n");
    }

    freeGame(&game);
}
