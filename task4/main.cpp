#include <iomanip>
#include <iostream>

/*
 Метеостанция: температура за несколько месяцев, в каждом дне 4 замера
 (ночь, утро, день, вечер). Программа считает для каждого месяца среднюю
 температуру и находит самый тёплый замер, потом печатает отчёт.

 int*** - data[месяц][день][замер]. Число месяцев и число дней в каждом
 месяце вводятся с клавиатуры, и у месяцев оно разное (28, 30, 31...).
 Значит все три уровня выделяются через new: data - массив месяцев,
 data[i] - массив дней i-го месяца, data[i][j] - замеры за день.
 Статический int[12][31][4] либо тратил бы память, либо не позволял
 бы задать произвольное количество.

 void* - отчёт состоит из значений разного типа: название месяца (char*),
 указатель прямо на ячейку с максимумом внутри data (int*) и среднее
 (double*). Чтобы хранить их в одном массиве и печатать одним циклом,
 храним void* + букву с типом, а при печати приводим обратно.

 Формат ввода:
 M
 название_месяца D   (D >= 1)
 D строк по 4 числа
 ...
*/

int main() {
  const int kMeasures = 4;

  int m = 0;
  std::cin >> m;
  if (m <= 0) {
    return 0;
  }

  char** names = new char*[m];
  int* days = new int[m];
  int*** data = new int**[m];

  for (int i = 0; i < m; i++) {
    names[i] = new char[32];
    std::cin >> names[i] >> days[i];
    data[i] = new int*[days[i]];
    for (int j = 0; j < days[i]; j++) {
      data[i][j] = new int[kMeasures];
      for (int k = 0; k < kMeasures; k++) {
        std::cin >> data[i][j][k];
      }
    }
  }

  double* avg = new double[m];
  int reportSize = 3 * m;
  void** report = new void*[reportSize];
  char* types = new char[reportSize];
  int pos = 0;

  for (int i = 0; i < m; i++) {
    int sum = 0;
    int* hottest = &data[i][0][0];
    for (int j = 0; j < days[i]; j++) {
      for (int k = 0; k < kMeasures; k++) {
        sum += data[i][j][k];
        if (data[i][j][k] > *hottest) {
          hottest = &data[i][j][k];
        }
      }
    }
    avg[i] = static_cast<double>(sum) / (days[i] * kMeasures);

    report[pos] = names[i];
    types[pos] = 's';
    pos++;
    report[pos] = &avg[i];
    types[pos] = 'd';
    pos++;
    report[pos] = hottest;
    types[pos] = 'i';
    pos++;
  }

  std::cout << std::fixed << std::setprecision(1);
  // печать отчёта: смотрим на тип и приводим void* обратно
  for (int p = 0; p < reportSize; p++) {
    if (types[p] == 's') {
      std::cout << static_cast<char*>(report[p]) << ": ";
    } else if (types[p] == 'd') {
      std::cout << "avg " << *static_cast<double*>(report[p]) << ", ";
    } else if (types[p] == 'i') {
      std::cout << "max " << *static_cast<int*>(report[p]) << std::endl;
    }
  }

  delete[] types;
  delete[] report;
  delete[] avg;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < days[i]; j++) {
      delete[] data[i][j];
    }
    delete[] data[i];
    delete[] names[i];
  }
  delete[] data;
  delete[] days;
  delete[] names;
  return 0;
}
