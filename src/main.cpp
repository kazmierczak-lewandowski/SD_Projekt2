#include "AVLTree.hpp"
#include "Collection.hpp"
#include "Heap.hpp"

#include <memory>
#include <ncurses.h>
#include <string>
#include <vector>

void menuLoop(const std::vector<std::string> &choices, int &highlight) {
  int choice = 0;
  while (choice != 10) {
    for (int i = 0; i < choices.size(); i++) {
      if (i == highlight) {
        attron(A_REVERSE);
      }
      mvprintw(i, 0, "%s", choices[i].c_str());
      attroff(A_REVERSE);
    }
    choice = getch();

    switch (choice) {
    case KEY_UP: {
      if (highlight != 0)
        highlight--;
      break;
    }
    case KEY_DOWN: {
      if (highlight != choices.size() - 1)
        highlight++;
      break;
    }
    default:
      break;
    }
  }
}
int getInput(const std::string &message) {
  clear();
  int input = 0;
  while (true) {
    printw("%s", message.c_str());
    scanw("%d", &input);
    if (input < 1) {
      printw("Niepoprawny wybor. Sprobuj ponownie.\n");
      continue;
    }
    return input;
  }
}
int main() {
  initscr();
  keypad(stdscr, true);
  curs_set(0);
  std::unique_ptr<Collection> collection = nullptr;
  std::vector<std::string> CHOICES{"1. Heap", "2. AVLTree", "3. Wyjdz"};
  int highlight = 0;
  menuLoop(CHOICES, highlight);
  switch (highlight) {
  case 0: {
    collection = std::make_unique<Heap>();
    break;
  }
  case 1: {
    collection = std::make_unique<AVLTree>();
    break;
  }
  default: {
    endwin();
    return 0;
  }
  }
  CHOICES = {"1. Dane z pliku numbers.txt",
             "2. Losowe dane",
             "3. Wypisz",
             "4. Wstaw",
             "5. Wypisz max",
             "6. Wyciagnij max",
             "7. Wysokosc",
             "8. Zmodyfikuj klucz",
             "9. Wyjdz"};
  do {
    highlight = 0;
    clear();
    menuLoop(CHOICES, highlight);
    switch (highlight) {
    case 0: {
      Collection::fillFromFile(*collection, "numbers.txt");
      clear();
      printw("Wypelniono danymi z pliku\n");
      getch();
      break;
    }
    case 1: {
      Collection::fillWithRandom(*collection, getInput("Podaj rozmiar: "));
      clear();
      printw("Wypelniono losowymi danymi\n");
      getch();
      break;
    }
    case 2: {
      collection->print();
      getch();
      break;
    }
    case 3: {
      const Element element(getInput("Podaj watosc do dodania: "),
                            getInput("Podaj priorytet do dodania: "));
      collection->insert(element);
      clear();
      printw("Dodano element\n");
      getch();
      break;
    }
    case 4: {
      clear();
      printw("%s", collection->peek().toString().c_str());
      getch();
      break;
    }
    case 5: {
      clear();
      printw("%s", collection->extractMax().toString().c_str());
      getch();
      break;
    }
    case 6: {
      clear();
      printw("%d", collection->getHeight());
    }
    case 7: {
      const Element element(getInput("Podaj warosc elementu do zmiany: "),
                            getInput("Podaj priorytet elementu do zmiany: "));
      const int newPriority =
          getInput("Podaj nowy priorytet");
      collection->modifyKey(element, newPriority);
      clear();
      printw("Zmieniono priorytet\n");
      getchar();
      break;
      }
    default:
      break;
    }
  } while (highlight != 6);
  endwin();
  return 0;
}