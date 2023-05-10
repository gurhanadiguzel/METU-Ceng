#ifndef _Node
#define _Node

template <class T>
class Node {
public:
  Node(const T& e = T(), Node *n = nullptr) :
      data(e), next(n) { }

  T data;
  Node *next;
};

#endif // _Node

