#include <iomanip>
#include <iostream>

struct MinMax {
  int min;
  int max;
};

double average(const int* temps, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += temps[i];
  }
  return static_cast<double>(sum) / n;
}

MinMax findMinMax(const int* temps, int n) {
  MinMax res{temps[0], temps[0]};
  for (int i = 1; i < n; i++) {
    if (temps[i] < res.min) res.min = temps[i];
    if (temps[i] > res.max) res.max = temps[i];
  }
  return res;
}

int countFrostDays(const int* temps, int n) {
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (temps[i] < 0) cnt++;
  }
  return cnt;
}

int main() {
  int n = 0;
  std::cin >> n;
  if (n <= 0) {
    return 0;
  }

  int* temps = new int[n];
  for (int i = 0; i < n; i++) {
    std::cin >> temps[i];
  }

  MinMax mm = findMinMax(temps, n);

  std::cout << std::fixed << std::setprecision(1) << average(temps, n)
            << std::endl;
  std::cout << mm.min << " " << mm.max << std::endl;
  std::cout << countFrostDays(temps, n) << std::endl;

  delete[] temps;
  return 0;
}
