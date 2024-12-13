#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY_MARKER '.'

int dimension;
char *game;

bool in(int i, int j) {
  return 0 <= i && i < dimension && 0 <= j && j < dimension;
}

void check(int i, int j, int i_step, int j_step) {
  int count = 0;
  char last_seen = '\0';

  while (in(i, j)) {
    if (game[i * dimension + j] != last_seen) {
      count = 0;
    }
    last_seen = game[i * dimension + j];
    count++;

    i += i_step;
    j += j_step;
  }

  if (count == dimension && last_seen != EMPTY_MARKER) {
    printf("\n%c wins\n", last_seen);
  }
}

int main(int argc, char *argv[]) {
  // receive the game state from stdin
  scanf("%d", &dimension);
  game = malloc(dimension * dimension * sizeof(char));
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      scanf(" %c ", &game[i * dimension + j]);
    }
  }

  // print game state
  for (int i = 0; i < dimension; i++) {
    for (int j = 0; j < dimension; j++) {
      printf("%c", game[i * dimension + j]);
    }
    printf("\n");
  }

  // search vertical and horizontal lines for a winner
  for (int i = 0; i < dimension; i++) {
    check(i, 0, 0, 1); // ith line
    check(0, i, 1, 0); // ith column
  }
  // search diagonals
  check(0, 0, 1, 1);              // main diagonal
  check(dimension - 1, 0, -1, 1); // antidiagonal

  return 0;
}
