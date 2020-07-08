#include <iostream>
#include <cassert>
#include "FibonacciPQ.h"

using namespace std;

int main() {
  FibonacciPQ<int> pq;
  assert(pq.empty());
  cout << "Pass\n";
  pq.push(5);
  assert(pq.top() == 5);
  cout << "Pass\n";
  pq.push(2);
  pq.push(10);
  assert(pq.top() == 2);
  cout << "Pass\n";
  assert(pq.size() == 3);
  cout << "Pass\n";
  pq.push(6);
  pq.push(20);
  pq.pop_top();
  assert(pq.top() == 5);
  cout << "Pass\n";
  assert(pq.size() == 4);
  cout << "Pass\n";
  pq.pop_top();
  assert(pq.top() == 6);
  cout << "Pass\n";
  return 0;
}