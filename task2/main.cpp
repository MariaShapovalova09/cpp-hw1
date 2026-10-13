#include <cstring>
#include <iostream>

// все операции одного типа: получают сумму по ссылке,
// аргумент (если он нужен) читают сами
void deposit(int& money) {
  int k = 0;
  std::cin >> k;
  if (k <= 0) {
    std::cout << "error" << std::endl;
    return;
  }
  money += k;
}

void withdraw(int& money) {
  int k = 0;
  std::cin >> k;
  if (k <= 0 || k > money) {
    std::cout << "error" << std::endl;
    return;
  }
  money -= k;
}

void balance(int& money) { std::cout << money << std::endl; }

void reset(int& money) { money = 0; }

// своя команда: удвоить сумму
void doubleMoney(int& money) { money *= 2; }

const int kCommandsCount = 5;
const char* names[kCommandsCount] = {"deposit", "withdraw", "balance", "reset",
                                     "double"};
void (*operations[kCommandsCount])(int&) = {deposit, withdraw, balance, reset,
                                            doubleMoney};

int main() {
  int money = 0;
  char cmd[64];

  while (std::cin >> cmd) {
    if (std::strcmp(cmd, "stop") == 0) {
      break;
    }

    int idx = -1;
    for (int i = 0; i < kCommandsCount; i++) {
      if (std::strcmp(cmd, names[i]) == 0) {
        idx = i;
        break;
      }
    }

    if (idx == -1) {
      std::cout << "error" << std::endl;
      std::cin.ignore(1000, '\n');  // пропускаем остаток строки
    } else {
      operations[idx](money);
    }
  }
  return 0;
}
