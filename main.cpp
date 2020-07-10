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
  priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > real;
  random_device rand;
  for (size_t i = 0; i < 100; i++) {
    unsigned int rd = rand() % 200;
    test.push(rd);
    real.push(rd);
    if (i > 0 && i % 5 == 0) {
      test.pop_top();
      real.pop();
      unsigned int a = test.top(), b = real.top();
      if (a != b) {
        cout << "ERROR\n";
      } // if different
    } //pop, compare
  } //for
  cout << "PASS\n";
  return 0;
}