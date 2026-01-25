#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <vector>

// min_heap
class Priority_Queue
{
private:
    int* arr;
    void heapify(int i);
    void heapify_down();
    int size {};
    int cap{};

public:
    Priority_Queue();
    ~ Priority_Queue();
    int parent(int key);
    int left(int key);
    int right(int key);

    void insert(int val);
    int pop();
    int top();

    void resize(); 

    bool empty() const;
    int get_size() const;

};


#endif