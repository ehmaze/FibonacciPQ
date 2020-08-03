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
  test.push(1);
  test.push(4);
  test.push(0);
  test.push(3);
  test.push(5);
  test.push(6);
  test.push(7);
  test.push(8);
  test.push(9);
  test.push(10);
  test.push(11);
  test.pop();
  test.push(12);
  test.push(13);
  FibonacciPQ<unsigned int>::Node *n = test.push(14);
  test.decrease_key(n, 2);
  test.pop();
  assert(test.top() == 2);
  unsigned int i = 3;
  while (!test.empty()) {
    test.pop();
    if (!test.empty()) (test.top() == i);
    i++;
  }
  cout << "Pass\n";
}