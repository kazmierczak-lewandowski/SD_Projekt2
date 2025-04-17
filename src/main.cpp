#include "Heap.hpp"
#include "ncurses.h"

int main() {
  initscr();
  Element elements[] ={{11, 11}, {22, 22}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}};
  Heap heap(elements, 10);
  heap.print();
  getch();
  getch();
  endwin();
  return 0;
}
