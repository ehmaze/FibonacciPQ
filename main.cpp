#include <iostream>
#include <cassert>
#include <queue>
#include <cstdint>
#include <random>
#include <vector>
#include <functional>
#include "FibonacciPQ.h"

using namespace std;

int main() {
  FibonacciPQ<unsigned int> test;
  priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>> real;
  random_device r;
  for (int i = 0; i < 5000; ++i) {
    unsigned int rd = r();
    test.push(rd);
    real.push(rd);
    if (rd % 4 == 0) {
      test.pop();
      real.pop();
    }
    if (test.size() > 0) assert(test.top() == real.top());
  }
  cout << "Pass\n";
}