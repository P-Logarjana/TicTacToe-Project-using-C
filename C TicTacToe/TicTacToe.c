#include <stdio.h>
#include <string.h>

#define SIZE 3
#define MAX_NAME_LENGTH 20

void printBoard(char board[SIZE][SIZE]);
void makeMove(char board[SIZE][SIZE], char player, const char* playerName);
int checkWin(char board[SIZE][SIZE]);
int isFull(char board[SIZE][SIZE]);

int main() {
    char board[SIZE][SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char player1Name[MAX_NAME_LENGTH];
    char player2Name[MAX_NAME_LENGTH];
    char currentPlayerName[MAX_NAME_LENGTH];

    printf("Enter name for Player X: ");
    fgets(player1Name, MAX_NAME_LENGTH, stdin);
    player1Name[strcspn(player1Name, "\n")] = 0; // Remove newline character

    printf("Enter name for Player O: ");
    fgets(player2Name, MAX_NAME_LENGTH, stdin);
    player2Name[strcspn(player2Name, "\n")] = 0; // Remove newline character

    char currentPlayer = 'X';
    strcpy(currentPlayerName, player1Name);
    int winner = 0;

    while (1) {
        printBoard(board);
        makeMove(board, currentPlayer, currentPlayerName);

        winner = checkWin(board);
        if (winner) {
            printBoard(board);
            printf("%s (Player %c) wins!\n", currentPlayerName, currentPlayer);
            break;
        }

        if (isFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        if (currentPlayer == 'X') {
            currentPlayer = 'O';
            strcpy(currentPlayerName, player2Name);
        } else {
            currentPlayer = 'X';
            strcpy(currentPlayerName, player1Name);
        }
    }

    return 0;
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

void makeMove(char board[SIZE][SIZE], char player, const char* playerName) {
    int move;
    while (1) {
        printf("%s (Player %c), enter your move (1-9): ", playerName, player);
        scanf("%d", &move);
        move--; // Adjust for 0-indexed array
        int row = move / SIZE;
        int col = move % SIZE;
        if (move >= 0 && move < SIZE * SIZE && board[row][col] == '1' + move) {
            board[row][col] = player;
            break;
        } else {
            printf("Invalid move, try again.\n");
        }
    }
}

int checkWin(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return 1;
    return 0;
}

int isFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return 0;
        }
    }
    return 1;
}
