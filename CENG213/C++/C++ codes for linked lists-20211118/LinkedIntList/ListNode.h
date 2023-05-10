#ifndef _Node
#define _Node
class ListNode{
  public:
    int data;
    ListNode *next;

    ListNode(int x) {
        data = x;
        next = nullptr;
    }

    ListNode(int x, ListNode *p) {
        data = x;
        next = p;
    }
};

#endif // _Node
