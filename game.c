#include <stdbool.h>
#include <stdio.h>
#include "game_core.h"

//see game.h for details
bool step(const int c, const int r, const int width, const int height) {
  if (c < 0 || c >= width || r < 0 || r >= height) {
    return false;
  }
  if (map[width * r + c] != UNKNOWN) return false;
  if (mine_at(c, r)) {
    map[width * r + c] = MINE;
    return true;
  }
  map[width * r + c] = 
    mine_at(c + 1, r) 
    + mine_at(c - 1, r)
    + mine_at(c, r + 1)
    + mine_at(c, r - 1)
    + mine_at(c + 1, r + 1)
    + mine_at(c - 1, r - 1)
    + mine_at(c - 1, r + 1)
    + mine_at(c + 1, r - 1); 
  return false;
}


//see game.h for details
bool step_adv(const int c, const int r, const int width, const int height) {
  if (c < 0 || c >= width || r < 0 || r >= height) {
    return false;
  }
  if (map[width * r + c] != UNKNOWN) return false;
  if (mine_at(c, r)) {
    map[width * r + c] = MINE;
    return true;
  }
  map[width * r + c] = 
    mine_at(c + 1, r) 
    + mine_at(c - 1, r)
    + mine_at(c, r + 1)
    + mine_at(c, r - 1)
    + mine_at(c + 1, r + 1)
    + mine_at(c - 1, r - 1)
    + mine_at(c - 1, r + 1)
    + mine_at(c + 1, r - 1);
  if (map[width * r + c] == 0) {
    step_adv(c + 1, r, width, height);
    step_adv(c - 1, r, width, height);
    step_adv(c, r + 1, width, height);
    step_adv(c, r - 1, width, height);
    step_adv(c + 1, r + 1, width, height);
    step_adv(c - 1, r - 1, width, height);
    step_adv(c - 1, r + 1, width, height);
    step_adv(c + 1, r - 1, width, height);
  }
  return false;
}


//see game.h for details
bool mark(const int c, const int r, int width, int height) {
  if (c < 0 || c >= width || r < 0 || r >= height) {
    return all_marked();
  }
  if (map[width * r + c] == UNKNOWN) {
    map[width * r + c] = MARKED;
    return all_marked();
  }
  if (map[width * r + c] == MARKED) {
    map[width * r + c] = UNKNOWN;
    return all_marked();
  }
  return all_marked();
}

//see game.h for details
void print(int width, int height) {
  for (int i = 0; i < height; i++) {
    int a = map[width * i];
    if (a == UNKNOWN) printf("_");
    else if (a == MARKED) printf("P");
      else if (a == MINE) printf("X");
      else printf("%d", a);
      for (int j = 1; j < width; j++) {
      a = map[width * i + j];
      if (a == UNKNOWN) printf(" _");
      else if (a == MARKED) printf(" P");
        else if (a == MINE) printf(" X");
        else printf(" %d", a);
        }
    printf("\n");
  }
}
