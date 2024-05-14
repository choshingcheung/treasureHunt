// File: treasureHunt.cpp
// Name: Cho Shing Cheung
// Date created: 05/03/2024
// Date modified: 05/04/2024
// Purpose of the file: This file contains the implementation for a 2D treasure hunt game played between a user and an AI. The game involves placing chests on a grid, digging for treasure, and trying to find all the chests placed by the opponent. It utilizes dynamic arrays for game boards, simulation of AI behavior, and basic I/O for user interaction.

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cctype>

const int krows = 10;
const int kcols = 10;
const int chestAmounts = 5;
int** userBoard = new int*[krows];
int** aiBoard = new int*[krows];
int userChestsFound[5] = {0}; // Tracks the number of pieces found for each chest type
int aiChestsFound[5] = {0};   // Same for AI

/*
 * Attempts to place a treasure chest on a specified board with the given orientation and starting position.
 * Ensures that the placement is within the boundaries and does not overlap with existing chests.
 *
 * @param array Pointer to the 2D game board array.
 * @param offsetRow Starting row index for the chest placement.
 * @param offsetCol Starting column index for the chest placement.
 * @param x Chest identifier (11 to 15) where each number corresponds to a different chest type.
 * @param rowOrCol Orientation of the chest (0 for horizontal, 1 for vertical).
 * @return True if the chest is placed successfully, false if it violates placement rules.
 */
bool placeChest(int **array, int offsetRow, int offsetCol, int x, int rowOrCol){

  int n = 16 - x;
  //Case 1: Modifying horizontally
  if(rowOrCol == 0){
    //Checking if the chest is off of the board grid
    if((offsetCol + n) > kcols){
      return false;
    }
    for(int j = offsetCol; j < (offsetCol + n); j++){
      //Checking if any another chests were placed
      if(array[offsetRow][j] != 0){
        return false;
      }
    }
    for(int j = offsetCol; j < (offsetCol + n); j++){
      //Placing the chest after checking validity
      array[offsetRow][j] = x;
    }
  }

  //Case 2: Modifying vertically
  else if(rowOrCol == 1){
    //Checking if the chest is off of the board grid
    if((offsetRow + n) > krows){
      return false;
    }
    for(int i = offsetRow; i < (offsetRow + n); i++){
      //Checking if any another chests were placed
      if(array[i][offsetCol] != 0){
        return false;
      }
    }
    for(int i = offsetRow; i < (offsetRow + n); i++){
      //Placing the chest after checking validity
      array[i][offsetCol] = x;
    }
  }

  return true;
}

/*
 * Displays the game board to the user, where each cell is represented by a specific character.
 * Empty cells are shown as '-', dug cells with no treasure as 'X', and cells where treasure was found are shown as '@'.
 *
 * @param board Constant pointer to the game board array.
 * @param row Number of rows in the board.
 * @param col Number of columns in the board.
 * @return Always returns 0 indicating the function executed successfully.
 */
int show(int **board, const int row, const int col){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      if(board[i][j] == 0){
        printf("%5c", '-');
      }
      else if(board[i][j] == -1){
        printf("%5c", 'X');
      }
      else if(board[i][j] < 0){
        printf("%5c", '@');
      }
      else{
        printf("%5c", '-');
      }
    }
    printf("\n");
  }
  return 0;
}

/*
 * Reveals the contents of the game board for debugging or review purposes, showing all treasures and their statuses.
 * Displays different characters based on whether a treasure is present, its type, and whether it has been dug up.
 *
 * @param board Constant pointer to the game board array.
 * @param row Number of rows in the board.
 * @param col Number of columns in the board.
 * @return Always returns 0 indicating the function executed successfully.
 */
int reveal(int **board, const int row, const int col){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      if(board[i][j] == 0){
        printf("%5c", '-');
      }
      else if(board[i][j] == -1){
        printf("%5c", 'X');
      }
      else if(board[i][j] > 0){
        if(board[i][j] == 11){
          printf("%5c", 'a');
        }
        else if(board[i][j] == 12){
          printf("%5c", 'b');
        }
        else if(board[i][j] == 13){
          printf("%5c", 'c');
        }
        else if(board[i][j] == 14){
          printf("%5c", 'd');
        }
        else if(board[i][j] == 15){
          printf("%5c", 'e');
        }
      }
      else{
        if(board[i][j] == -11){
          printf("%5c", 'A');
        }
        else if(board[i][j] == -12){
          printf("%5c", 'B');
        }
        else if(board[i][j] == -13){
          printf("%5c", 'C');
        }
        else if(board[i][j] == -14){
          printf("%5c", 'D');
        }
        else if(board[i][j] == -15){
          printf("%5c", 'E');
        }
      }
    }
    printf("\n");
  }
  return 0;
}

/*
 * Executes a digging action at the specified location on the game board.
 * Updates the cell based on whether a treasure was found and tracks the progress of treasure discovery.
 *
 * @param board Game board array.
 * @param targetRow Row index where the dig action is attempted.
 * @param targetCol Column index where the dig action is attempted.
 * @param chestsFound Array tracking the number of pieces found for each type of chest.
 * @return 0 if the action was processed, even if nothing was found or the cell was already dug.
 */
int dig(int **board, int targetRow, int targetCol, int *chestsFound){
  
  if (board[targetRow][targetCol] == -1) {
      printf("You've already dug here!\n");
      return 0;
  }

  if(board[targetRow][targetCol] > 0){
      int chestCode = board[targetRow][targetCol];
      int chestIndex = chestCode - 11; // Convert chest code to index
      int chestSize = 16 - chestCode; // Calculate size of the chest correctly
    
      // Mark as dug
      board[targetRow][targetCol] = -chestCode;
      // Update found chests
      chestsFound[chestIndex]++;

      // Check if the whole chest is dug up
      if(chestsFound[chestIndex] == chestSize){
          printf("All parts of a %d-sized chest have been dug up!\n", chestSize);
      }
    } 
    else if (board[targetRow][targetCol] == 0) {
      board[targetRow][targetCol] = -1;
    }
  
    return 0;
}


/*
 * Initializes the game board, setting all cells to indicate they are empty.
 *
 * @param board Pointer to the game board array.
 * @param row Number of rows in the board.
 * @param col Number of columns in the board.
 */
void initializeBoard(int** board, const int row, const int col){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      board[i][j] = 0;
    }
  }
}

/*
 * Checks and executes the placement of a chest on the game board. It prints the result and updates the board visually if the placement is successful.
 *
 * @param board Pointer to the game board array where the chest will be placed.
 * @param rowLocation Row index for placing the chest.
 * @param colLocation Column index for placing the chest.
 * @param chestType Numeric identifier for the type of chest.
 * @param horiVert Orientation of chest placement (0 for horizontal, 1 for vertical).
 * @return True if the chest is placed successfully, false otherwise.
 */
bool placeChestChecker(int **board, int rowLocation, int colLocation, int chestType, int horiVert){
  bool placeChestChecker;

  placeChestChecker = placeChest(board, rowLocation, colLocation, chestType, horiVert); // Horizontal placement
  if(placeChestChecker == true){
    printf("Chest placed successfully!\n");
  }
  else{
    return false;
  }

  return true;
}

/*
 * Handles user input for placing chests on the user's game board. It prompts the user for chest type, orientation, and coordinates.
 * Validates the input and retries if the input is incorrect or if the placement fails.
 */
void userInput(){
  int chestType = 0;
  int rowLocation = 0;
  int colLocation = 0;
  int horiVert;
  int status = -1;
  char playAgain;
  int pointer = -1;

  while(status != 1 || chestType < 11 || chestType > 15){
    printf("\nWhat type of chest do you want to place? Enter '11' for bronze, '12' for silver, '13' for gold, '14' for rubies, and '15' for vibranium: ");
    status = scanf("%d", &chestType);
    if(status != 1 || chestType < 11 || chestType > 15){
      printf("Your input is invalid! You should enter a positive integer between 11 and 15! Try again!\n");
    }
    printf("\n");
  }

  status = -1;
  while(status != 1 || horiVert < 0 || horiVert > 1){
    printf("Do you want to place the chest horizontally or vertically? Enter 0 for horizontal, 1 for vertical: ");
    status = scanf("%d", &horiVert);
    if(status != 1 || horiVert < 0 || horiVert > 1){
      printf("Your input is invalid! You should enter a positive integer between 0 and 1! Try again!\n");
    }
    printf("\n");
  }

  status = -1;
  while(status != 1){
    printf("Which row do you want to place the chest? ");
    status = scanf("%d", &rowLocation);
    if(status != 1){
      printf("Your input is invalid! You should enter a positive integer! Try again!\n");
    }
    printf("\n");
  }

  status = -1;
  while(status != 1){
    printf("Which column do you want to place the chest? ");
    status = scanf("%d", &colLocation);
    if(status != 1){
      printf("Your input is invalid! You should enter a positive integer! Try again!\n");
    }
    printf("\n");
  }

  if(!placeChestChecker(userBoard, rowLocation, colLocation, chestType, horiVert)){
    printf("Failed to place chest. Check to see if you have entered valid values! \n");
    userInput();
  }
}

/*
 * Automatically generates input for placing chests on the AI's game board. It randomly selects chest types, orientations, and coordinates until a valid placement is achieved.
 */
void aiInput(){
  srand(time(NULL));
  int chestType = ((rand() % 5) + 11);
  int rowLocation = (rand() % krows);
  int colLocation = (rand() % kcols);
  int horiVert = (rand() % 2);

  // Retry loop until successful placement
  while(!placeChestChecker(aiBoard, rowLocation, colLocation, chestType, horiVert)){
    rowLocation = rand() % krows;
    colLocation = rand() % kcols;
  }
}

/*
 * Checks if all chests on a given board have been found, which would indicate the end of the game.
 *
 * @param board The game board to check for remaining treasures.
 * @return True if no chests remain unexposed, otherwise false.
 */
bool gameEnd(int **board){
  for(int i = 0; i < krows; i++){
    for(int j = 0; j < kcols; j++){
      if(board[i][j] > 0){
        return false;
      }
    }
  }
  return true;
}

/*
 * Properly deallocates all dynamic memory used for the game boards to avoid memory leaks. This function should be called before the program exits.
 */
void cleanup(){
  for(int i = 0; i < krows; i++) {
    delete[] userBoard[i]; 
    delete[] aiBoard[i];
  }
  delete[] userBoard; 
  delete[] aiBoard;
}

/*
 * Main game loop that initializes the game, handles gameplay, and cleans up resources.
 * The loop continues until all treasures have been found on either the user's or AI's board.
 */
int main(int argc, char** argv) {
  bool placeChestChecker;
  int digRow = 0;
  int digCol = 0;
  int status = -1;

  // Setting up the 2D array ogBoard
  for(int i = 0; i < krows; i++){
    userBoard[i] = new int[kcols];
    aiBoard[i] = new int[kcols];
  }

  initializeBoard(userBoard, krows, kcols);
  initializeBoard(aiBoard, krows, kcols);

 // Attempt to place chests in different scenarios
  printf("\n____________________Placing Chests (User) ____________________\n");
  for(int i = 0; i < chestAmounts; i++){
    printf("You have %d chests to place!\n\n", (chestAmounts - i));
    reveal(userBoard, krows, kcols);
    userInput();
  }
  printf("\n____________________Placing Chests (AI) ____________________\n");
  for(int i = 0; i < chestAmounts; i++){
    aiInput();
  }

  while(!gameEnd(userBoard) && !gameEnd(aiBoard)){
    while(status != 2 || digRow < 0|| digRow > krows || digCol < 0 || digCol > kcols){
      printf("\n____________________User Board____________________\n");
      reveal(userBoard, krows, kcols);
      printf("\n_____________________AI Board_____________________\n");
      show(aiBoard, krows, kcols);
      printf("Please choose a row and a column location to dig: ");
      status = scanf("%d %d", &digRow, &digCol);
      if(status != 2 || digRow < 0|| digRow > krows || digCol < 0 || digCol > kcols){
        printf("The value you input is invalid! Try Again!\n");
      }
    }
    dig(aiBoard, digRow, digCol, userChestsFound); // User digs on AI board
    if(!gameEnd(aiBoard)){
      digRow = rand() % krows;
      digCol = rand() % kcols;
      dig(userBoard, digRow, digCol, aiChestsFound); // AI digs on user board
      status = -1;
    }
  }

  if(gameEnd(userBoard)){
    printf("All treasures found! AI wins!\n");
  }
  else{
    printf("All treasures found! User wins!\n");
  }
  
  // Deallocates Memory
  cleanup();
  return 0;
}

/* Parts of the Sample Output with using setting two maximum chests to be put.

____________________Placing Chests (User) ____________________
You have 2 chests to place!

    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -

What type of chest do you want to place? Enter '11' for bronze, '12' for silver, '13' for gold, '14' for rubies, and '15' for vibranium: 11

Do you want to place the chest horizontally or vertically? Enter 0 for horizontal, 1 for vertical: 0

Which row do you want to place the chest? 0

Which column do you want to place the chest? 0

Chest placed successfully!
You have 1 chests to place!

    a    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -

What type of chest do you want to place? Enter '11' for bronze, '12' for silver, '13' for gold, '14' for rubies, and '15' for vibranium: 15

Do you want to place the chest horizontally or vertically? Enter 0 for horizontal, 1 for vertical: 9
Your input is invalid! You should enter a positive integer between 0 and 1! Try again!

Do you want to place the chest horizontally or vertically? Enter 0 for horizontal, 1 for vertical: 0

Which row do you want to place the chest? 9

Which column do you want to place the chest? 9

Chest placed successfully!

____________________Placing Chests (AI) ____________________
Chest placed successfully!
Chest placed successfully!

____________________User Board____________________
    a    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    e

_____________________AI Board_____________________
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
Please choose a row and a column location to dig: 0 0

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    e

_____________________AI Board_____________________
    X    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
Please choose a row and a column location to dig: 9 9

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    e

_____________________AI Board_____________________
    X    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 0 1

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    e

_____________________AI Board_____________________
    X    X    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 0 2

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    e

_____________________AI Board_____________________
    X    X    X    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 0 3

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    X    -    -    -    e

_____________________AI Board_____________________
    X    X    X    X    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 0 4

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    X    -    -    -    e

_____________________AI Board_____________________
    X    X    X    X    @    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 0 5

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    X    -    -    -    e

_____________________AI Board_____________________
    X    X    X    X    @    X    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 1 4

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    X    -    -    -    e

_____________________AI Board_____________________
    X    X    X    X    @    X    -    -    -    -
    -    -    -    -    @    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 2 4

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    X    -    -    -    e

_____________________AI Board_____________________
    X    X    X    X    @    X    -    -    -    -
    -    -    -    -    @    -    -    -    -    -
    -    -    -    -    @    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 3 4

____________________User Board____________________
    A    a    a    a    a    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
    -    X    -    -    -    -    X    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    X    -    -    -
    -    -    -    -    X    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    X    X    -    -    -    e

_____________________AI Board_____________________
    X    X    X    X    @    X    -    -    -    -
    -    -    -    -    @    -    -    -    -    -
    -    -    -    -    @    -    -    -    -    -
    -    -    -    -    @    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    -
    -    -    -    -    -    -    -    -    -    X
Please choose a row and a column location to dig: 4 4
All parts of a 5-sized chest have been dug up!
*/