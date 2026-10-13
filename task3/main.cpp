#include <cstring>
#include <iostream>

const int kRows = 5;
const int kCols = 10;

void clearBoard(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; y++) {
    for (int x = 0; x < kCols; x++) {
      board[y][x] = ' ';
    }
  }
}

bool inside(int x, int y) { return x >= 0 && x < kCols && y >= 0 && y < kRows; }

bool put(char board[kRows][kCols], int x, int y, char c) {
  if (!inside(x, y)) {
    return false;
  }
  board[y][x] = c;
  return true;
}

bool text(char board[kRows][kCols], int x, int y, const char* word) {
  int len = std::strlen(word);
  // сначала проверяем первую и последнюю букву, потом уже пишем
  if (!inside(x, y) || !inside(x + len - 1, y)) {
    return false;
  }
  for (int i = 0; i < len; i++) {
    put(board, x + i, y, word[i]);
  }
  return true;
}

void printBoard(const char board[kRows][kCols]) {
  for (int y = 0; y < kRows; y++) {
    for (int x = 0; x < kCols; x++) {
      std::cout << board[y][x];
    }
    std::cout << std::endl;
  }
}

int main() {
  char board[kRows][kCols];
  clearBoard(board);

  char cmd[64];
  while (std::cin >> cmd) {
    if (std::strcmp(cmd, "quit") == 0) {
      break;
    }

    if (std::strcmp(cmd, "clear") == 0) {
      clearBoard(board);
    } else if (std::strcmp(cmd, "put") == 0) {
      int x = 0, y = 0;
      char c = ' ';
      std::cin >> x >> y >> c;
      if (!put(board, x, y, c)) {
        std::cout << "error" << std::endl;
      }
    } else if (std::strcmp(cmd, "text") == 0) {
      int x = 0, y = 0;
      char word[64];
      std::cin >> x >> y >> word;
      if (!text(board, x, y, word)) {
        std::cout << "error" << std::endl;
      }
    } else if (std::strcmp(cmd, "print") == 0) {
      printBoard(board);
    } else {
      std::cout << "error" << std::endl;
      std::cin.ignore(1000, '\n');
    }
  }
  return 0;
}
