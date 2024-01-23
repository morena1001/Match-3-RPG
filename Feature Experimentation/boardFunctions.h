#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <time.h>
#include "piece.h"

using namespace std;

void generateNewPieces(piece board[5][7]);
void executeMoves(piece board[5][7]);
void printBoard(piece board[5][7]);
void matchChecking(piece board[5][7]);
void pieceShuffle(piece board[5][7]);
void getMoves(piece board[5][7]);


void generateNewPieces(piece board[5][7]) {
    srand(time(NULL));
    // Generate a new piece for the empty tiles
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            if (board[i][j].num == 0) {
                board[i][j].num = 1 + (rand() % 5);
            }
        }
    }
}

void executeMoves(piece board[5][7]) {

}

void printBoard(piece board[5][7]) {
    cout << " Y 1 2 3 4 5 6 7" << endl << "X"<< endl;
    for(int i = 0; i < 5; i++) {
        cout << i + 1 << "  ";
        for(int j = 0; j < 7; j++) {
            cout << board[i][j].num << " ";
        }
        cout << endl;
    }
}

void matchChecking(piece board[5][7]) {
    srand(time(NULL));

    bool leftPieces;
    bool rightPieces;
    bool topPieces;
    bool bottomPieces;
    
    // Check that the generated piece is not in a match of 3
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 7; j++) {
            leftPieces = j > 1 && board[i][j].num == board[i][j - 1].num == board[i][j - 2].num;
            rightPieces = j < 5 && board[i][j].num == board[i][j + 1].num == board[i][j + 2].num;
            topPieces = i > 1 && board[i][j].num == board[i - 1][j].num == board[i - 2][j].num;
            bottomPieces = i < 4 && board[i][j].num == board[i + 1][j].num == board[i + 2][j].num;

            // Check pieces around tile
            while (leftPieces || rightPieces || topPieces || bottomPieces) {
                board[i][j].num = 1 + (board[i][j].num % 5);

                leftPieces = j > 1 && board[i][j].num == board[i][j - 1].num == board[i][j - 2].num;
                rightPieces = j < 5 && board[i][j].num == board[i][j + 1].num == board[i][j + 2].num;
                topPieces = i > 1 && board[i][j].num == board[i - 1][j].num == board[i - 2][j].num;
                bottomPieces = i < 4 && board[i][j].num == board[i + 1][j].num == board[i + 2][j].num;
            }
        }
    }
}

void pieceShuffle(piece board[5][7]) {

}

void getMoves(piece board[5][7]) {
    string xPosition, yPosition, direction = "";
    int xCoordinate, yCoordinate;
    int movesLeft = 3;

    do {
        cout << "What piece do want to move? { " << movesLeft << " moves left } : ";
        cin >> xPosition >> yPosition >> direction;

        if(stoi(xPosition) < 1 || stoi(xPosition) > 5) {
            cout << "X coordinate is out of bounds, try another input" << endl;
        }
        
        else if(stoi(yPosition) < 1 || stoi(yPosition) > 7) {
            cout << "Y coordinate is out of bounds, try another input" << endl;
        }
        
        else if(direction != "right" && direction != "left" && direction != "up" && direction != "down") {
            cout << "Incorrect direction, try another input" << endl;
        }

        else if((stoi(xPosition) == 1 && direction == "up") || (stoi(xPosition) == 5 && direction == "down") ||
            (stoi(yPosition) == 1 && direction == "left") || (stoi(yPosition) == 7 && direction == "right")) {
            cout << "Direction not possible, try another input" << endl;
        }

        else {
            xCoordinate = stoi(xPosition) + 1;
            yCoordinate = stoi(yPosition) + 1;
            if(board[xCoordinate][yCoordinate].matched) {
                cout << "Piece already matched, try another input" << endl;
                continue;
            }

            int temp = board[xCoordinate][yCoordinate].num;
            if (direction == "up") {
                if (board[xCoordinate + 1][yCoordinate].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate].num = board[xCoordinate + 1][yCoordinate].num;
                board[xCoordinate + 1][yCoordinate].num = temp;
            }

            else if (direction == "down") {
                if (board[xCoordinate - 1][yCoordinate].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate].num = board[xCoordinate - 1][yCoordinate].num;
                board[xCoordinate - 1][yCoordinate].num = temp;
            }

            else if (direction == "left") {
                if (board[xCoordinate][yCoordinate - 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate].num = board[xCoordinate][yCoordinate - 1].num;
                board[xCoordinate][yCoordinate - 1].num = temp;
            }

            else if (direction == "right") {
                if (board[xCoordinate][yCoordinate + 1].matched) {
                    cout << "Piece you want to switch is already matched, try another input" << endl;
                    continue;
                }

                board[xCoordinate][yCoordinate].num = board[xCoordinate][yCoordinate + 1].num;
                board[xCoordinate][yCoordinate + 1].num = temp;
            }


            movesLeft--;
        }

        printBoard(board);
    } while (movesLeft > 0);
}
