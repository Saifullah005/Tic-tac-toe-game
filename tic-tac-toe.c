#include <stdio.h>
#include <string.h>

struct pos {
    int boardpos;
    int arrayindex;
};

struct pos positions[9] = {
    {0, 0}, {1, 2}, {2, 4},
    {3, 10}, {4, 12}, {5, 14},
    {6, 20}, {7, 22}, {8, 24}
};

int winningCombinations[8][3] = {
    {0, 1, 2}, 
    {3, 4, 5},
    {6, 7, 8},   
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6}
};

int getindex(int p) {
    for (int i = 0; i < 9; i++) {
        if (positions[i].boardpos == p)
            return positions[i].arrayindex;
    }
    return -1;
}

void printboard(char board[25][5]) {
    for (int i = 0; i < 25; i++) {
        printf("%s", board[i]);
        if ((i + 1) % 5 == 0)
            printf("\n");
    }
}

int checkWinner(int playerMoves[], int count) {
  int match ;
  for (int i = 0; i < 8; i++) {
      match = 0;
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < count; k++) {
                if (winningCombinations[i][j] == playerMoves[k]) {
                    match++;
                    break;
                }
            }
        }
        if (match == 3)
            return 1;
    }
    return 0;
}

int main() {
  char board[25][5] = {
    "[0]", " | ", "[1]", " | ", "[2]",
    "---", " | ", "---", " | ", "---",
    "[3]", " | ", "[4]", " | ", "[5]",
    "---", " | ", "---", " | ", "---",
    "[6]", " | ", "[7]", " | ", "[8]"
  };
  
  int player1[5] = {-1}, player2[5] = {-1};
  int position1 = 0, position2 = 0;
  int turn = 1, winner = 0;
  
  while (turn <= 9 && winner == 0) {
    printboard(board);
    int move; 
        printf("Player %d, enter your move (0-8): ",(turn % 2 == 1) ? 1 : 2);
        scanf("%d", &move);

        if (move < 0 || move > 8) {
            printf("Invalid move. Try between 0 and 8.\n");
            continue;
        }

        // Check if already taken
        int alreadyTaken = 0;
        for (int i = 0; i < position1; i++)
            if (player1[i] == move) alreadyTaken = 1;
        for (int i = 0; i < position2; i++)
            if (player2[i] == move) alreadyTaken = 1;

        if (alreadyTaken) {
            printf("That position is already taken.\n");
            continue;
        }

        
        int idx = getindex(move);
        if (turn % 2 == 1) {
            strcpy(board[idx], " X ");
            player1[position1++] = move;
            if (turn >= 5)
                winner = checkWinner(player1, position1);
        } else {
            strcpy(board[idx], " O ");
            player2[position2++] = move;
            if (turn >= 5)
                winner = checkWinner(player2, position2);
        }

        if (winner) {
            printboard(board);
            printf("=== Player %d WINS! ===\n", (turn % 2 == 1) ? 1 : 2);
            return 0;
        }

        turn++;
    }

    printboard(board);
    printf("=== It's a draw! ===\n");
    return 0;
}