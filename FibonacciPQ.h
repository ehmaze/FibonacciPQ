#pragma once

#include <functional>
#include <cstdint>
#include <cmath>
#include <exception>

#define PHI 1.61803398875

template<typename T, typename Comp = std::less<T>>
class FibonacciPQ {
public:
  class Node {
  public:
    Node(const T& datum_in) :
      datum(datum_in),
      parent(nullptr),
      child(nullptr),
      right(this),
      left(this),
      degree(0),
      mark(false) {
    }//Constructor

    const T& operator*() const {
      return datum;
    }//Derefrence

    friend FibonacciPQ;
  private:
    T datum;
    Node* parent;
    Node* child;
    Node* right;
    Node* left;
    std::size_t degree;
    bool mark;
  };//Node Class

  FibonacciPQ() :
    min(nullptr),
    siz(0) {
  }//Constructor

  FibonacciPQ(const FibonacciPQ& other) {
    //TODO
  }//Copy Ctor

  FibonacciPQ& operator=(const FibonacciPQ& rhs) {
    //TODO
  }//Assignment

  ~FibonacciPQ() {
    //TODO
  }//Destructor

  const std::size_t size() const {
    return siz;
  }//size

  bool empty() const {
    return siz == 0;
  }//empty

  const T& top() const {
    if (empty()) {
      throw std::bad_function_call();
    }
    return min->datum;
  }//top

  //Modified to return new node, as to maintain pointer to element for decrease key
  Node* push(const T& datum_in) {
    Node *n = new Node(datum_in);
    if (empty()) {
      min = n;
    }//if empty, make root
    else {
      n->right = min;
      n->left = min->left;
      min->left->right = n;
      min->left = n;
      Comp comp;
      if (comp(n->datum, min->datum)) {
        min = n;
      }//check if min
    } //Add to root list;
    siz++;
    return n;
  }//push

  void pop_top() {
    if (empty()) {
      throw std::bad_function_call();
    }//throw expection popping into empty heap
    delete extract_minimum_elt();
  }

private:

  //Returns min node, maintaining heap property
  Node* extract_minimum_elt() {
    Node* temp = min->child;
    if (temp) {
      do {
        temp->right->left = temp->left;
        temp->left->right = temp->right;
        temp->left = min->left;
        min->left->right = temp;
        min->left = temp;
        temp->right = min;
        temp->parent = nullptr;
        temp = temp->right;
      } while (temp != min->child); //while, make parent null
    }//if
    temp = min;
    temp->left->right = temp->right;
    temp->right->left = temp->left;
    if (temp == temp->right) {
      min = nullptr;
    }//if last element
    else {
      min = temp->right;
      consolidate();
    }//new min consolidate
    siz--;
    return temp;
  }//extract_min_elt

  //Consolidate tree after removing min element
  void consolidate() {
    int arr_size = (int)std::ceil(std::log(siz)/std::log(PHI)) + 1;
    Node** arr = new Node*[arr_size];
    for (int i = 0; i < arr_size; i++) {
      arr[i] = nullptr;
    }//for, initialize
    Comp comp;
    Node* temp = min;
    do {
      Node* x = temp;
      int deg = x->degree;
      while (arr[deg]) {
        Node* y = arr[deg];
        if (comp(y->datum, x->datum)) {
            Node *temp1 = x;
            x = y;
            y = temp1;
        } //if x > y, swap
        heap_link(y, x);
        arr[deg] = nullptr;
        deg++;
      }//while (arr[deg])
      arr[deg] = x;
      temp = temp->right;
    } while (temp != min); //for each node in root list
    min = nullptr;
    for (int i = 0; i < arr_size; i++) {
      if (arr[i] && !min) {
        arr[i]->right->left = arr[i]->left;
        arr[i]->left->right = arr[i]->right;
        arr[i]->right = arr[i];
        arr[i]->left = arr[i];
        min = arr[i];
      }//if root list empty
      else if (arr[i]) {
        arr[i]->right->left = arr[i]->left;
        arr[i]->left->right = arr[i]->right;
        arr[i]->left = min->left;
        min->left->right = arr[i];
        min->left = arr[i];
        arr[i]->right = min;
        if (comp(arr[i]->datum, min->datum)) {
          min = arr[i];
        }//if new min
      }//add to root list
    } //elements of array
  }//consolidate

  void heap_link(Node* y, Node* x) {
    y->left->right = y->right;
    y->right->left = y->left;
    x->child = y;
    y->parent = x;
    x->degree++;
    y->mark = false;
  }//heap_link

  Node* min;
  std::size_t siz;
};