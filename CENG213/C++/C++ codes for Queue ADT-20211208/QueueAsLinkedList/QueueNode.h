#ifndef _QUEUE
#define _QUEUE

template <class Object>
class QueueNode
{
    public:
        QueueNode(const Object& e = Object(), QueueNode* n = nullptr)
            : item(e), next(n) {}

        Object item;
        QueueNode* next;
};

#endif // _QUEUE
