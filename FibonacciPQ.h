#pragma once

#include <functional>
#include <cstdint>
#include <cmath>
#include <vector>
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
      std::vector<Node*> children;
      do {
        children.push_back(temp);
        temp = temp->right;
      } while (temp != min->child);// while, initializee children 
      for (std::size_t i = 0; i < children.size(); i++) {
        children[i]->right->left = children[i]->left;
        children[i]->left->right = children[i]->right;
        min->left->right = children[i];
        children[i]->left = min->left;
        children[i]->right = min;
        min->left = children[i];
        children[i]->parent = nullptr;
      }//for, add children to root list
    }//if min has children
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
    std::vector<Node*> arr(arr_size, nullptr);
    std::vector<Node*> root_list;
    Comp comp;
    Node* temp = min;
    do {
      root_list.push_back(temp);
      temp = temp->right;
    } while (temp != min); // fill root list vector
    for (std::size_t i = 0; i < root_list.size(); i++) {
      Node* x = root_list[i];
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
    }//for each node in root list
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
    if (x->child) {
      y->right = x->child;
      y->left = x->child->left;
      x->child->left->right = y;
      x->child->left = y;
    }
    else {
      y->right = y;
      y->left = y;
    }
    x->child = y;
    y->parent = x;
    x->degree += (y->degree + 1);
    y->mark = false;
  }//heap_link

  Node* min;
  std::size_t siz;
};