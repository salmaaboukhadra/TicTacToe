// tictactoe.cpp
// Salma Aboukhadra, CISP 360
// July 27, 2025

#include <iostream>
#include <cstdlib>  // For rand(), srand()
#include <ctime>    // For time()
#include <cctype>   // For tolower()

using namespace std;

// Constants
const int BOARD_SIZE = 9;
const char EMPTY = ' ';
const char HUMAN = 'X';
const char COMPUTER = 'O';

// Function prototypes
void ProgramGreeting();
void DisplayMenu();
int GetMenuChoice();
void ExplainGame();
void InitializeBoard(char board[]);
void DisplayBoard(const char board[]);
bool IsBoardFull(const char board[]);
bool CheckWin(const char board[], char player);
int GetHumanMove(const char board[]);
int GetComputerMove(const char board[]);
void UpdateBoard(char board[], int move, char player);
bool IsValidMove(const char board[], int move);
bool AskPlayAgain();
bool AskQuit();

// Main program
int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed random

    ProgramGreeting();

    while (true) {  // Specification A1 - Main Game Loop
        DisplayMenu();
        int choice = GetMenuChoice();

        if (choice == 1) {
            ExplainGame();
        } else if (choice == 2) {
            char board[BOARD_SIZE];
            InitializeBoard(board);

            // Specification C1 - Random Start
            bool humanTurn = (rand() % 2 == 0);
            cout << (humanTurn ? "Human" : "Computer") << " will start first." << endl;

            DisplayBoard(board);

            bool gameOver = false;
            while (!gameOver) {
                if (humanTurn) {
                    // Get human move
                    int move = GetHumanMove(board);
                    UpdateBoard(board, move, HUMAN);
                    DisplayBoard(board);

                    if (CheckWin(board, HUMAN)) {
                        cout << "Congratulations! You win!" << endl;
                        gameOver = true;
                    }
                } else {
                    // Specification C3 - AI (simple random move)
                    // Computer calculates its move here:
                    int move = GetComputerMove(board);
                    UpdateBoard(board, move, COMPUTER);
                    cout << "Computer chose position " << (move + 1) << "." << endl;
                    DisplayBoard(board);

                    if (CheckWin(board, COMPUTER)) {
                        cout << "Computer wins. Better luck next time!" << endl;
                        gameOver = true;
                    }
                }

                if (!gameOver && IsBoardFull(board)) {
                    cout << "It's a tie!" << endl;
                    gameOver = true;
                }

                humanTurn = !humanTurn;  // Switch turns
            }

            // Specification A2 - Simple Prompt to play again
            if (!AskPlayAgain()) {
                cout << "Thank you for playing Tic Tac Toe. Goodbye!" << endl;
                break;
            }
        } else if (choice == 3) {
            cout << "Goodbye!" << endl;
            break;
        }
    }

    return 0;
}

// ProgramGreeting function
void ProgramGreeting() {
    // Program Greeting
    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Author: Your Name" << endl;
    cout << "Due Date: February 14, 2021" << endl << endl;
}

// Display the main menu
void DisplayMenu() {
    cout << "Main Menu:" << endl;
    cout << "1. Explain Game" << endl;
    cout << "2. Play" << endl;
    cout << "3. Quit" << endl;
}

// Specification B2 - Valid Menu Choices
int GetMenuChoice() {
    int choice;
    while (true) {
        cout << "Enter your choice (1-3): ";
        if (cin >> choice && (choice >= 1 && choice <= 3)) {
            cin.ignore(10000, '\n');
            return choice;
        } else {
            cout << "Invalid choice. Please enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Explain the game briefly
void ExplainGame() {
    cout << "\nTic Tac Toe is a game where you play against the computer." << endl;
    cout << "Players alternate placing X's and O's on a 3x3 grid." << endl;
    cout << "The first player to get three in a row vertically, horizontally," << endl;
    cout << "or diagonally wins. If all spaces fill without a winner, it's a tie." << endl << endl;
}

// Specification A3 - Array Data Type
void InitializeBoard(char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = EMPTY;
    }
}

// Specification C2 - Simple Display
void DisplayBoard(const char board[]) {
    cout << "\n";
    for (int row = 0; row < 3; ++row) {
        cout << " ";
        for (int col = 0; col < 3; ++col) {
            int idx = row * 3 + col;
            cout << (board[idx] == EMPTY ? '-' : board[idx]);
            if (col < 2) cout << " | ";
        }
        cout << "\n";
        if (row < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}

// Check if board is full (tie)
bool IsBoardFull(const char board[]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i] == EMPTY)
            return false;
    }
    return true;
}

// Check if player has won
bool CheckWin(const char board[], char player) {
    // Rows
    for (int i = 0; i < 3; ++i) {
        if (board[i * 3] == player && board[i * 3 + 1] == player && board[i * 3 + 2] == player)
            return true;
    }
    // Columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] == player && board[i + 3] == player && board[i + 6] == player)
            return true;
    }
    // Diagonals
    if (board[0] == player && board[4] == player && board[8] == player)
        return true;
    if (board[2] == player && board[4] == player && board[6] == player)
        return true;

    return false;
}

// Specification B3 – Valid Move
int GetHumanMove(const char board[]) {
    int move;
    while (true) {
        cout << "Enter your move (1-9): ";
        if (cin >> move && move >= 1 && move <= 9) {
            move -= 1; // Convert to zero-based index
            if (IsValidMove(board, move)) {
                cin.ignore(10000, '\n');
                return move;
            } else {
                cout << "That position is already taken. Try again." << endl;
            }
        } else {
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// Check if move is valid
bool IsValidMove(const char board[], int move) {
    if (move < 0 || move >= BOARD_SIZE) return false;
    return board[move] == EMPTY;
}

// Specification C3 - AI
int GetComputerMove(const char board[]) {
    // Comment: Simple AI selects a random available position
    int move;
    do {
        move = rand() % BOARD_SIZE;
    } while (!IsValidMove(board, move));
    return move;
}

// Update the board at the given move
void UpdateBoard(char board[], int move, char player) {
    board[move] = player;
}

// Ask if user wants to play again
bool AskPlayAgain() {
    char answer;
    while (true) {
        cout << "Play again? (y/n): ";
        if (cin >> answer) {
            answer = tolower(answer);
            cin.ignore(10000, '\n');
            if (answer == 'y') return true;
            if (answer == 'n') return false;
        }
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
