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
  test.push(10);
  test.push(15);
  FibonacciPQ<unsigned int>::Node *n = test.push(20);
  test.push(13);
  test.push(2);
  test.push(4);
  test.pop();
  test.push(9);
  test.decrease_key(n, 1);
  assert(test.top() == 1);
  test.pop();
  assert(test.top() == 4);
  cout << "Pass\n";
}