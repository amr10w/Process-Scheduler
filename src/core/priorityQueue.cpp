#include "priorityQueue.h"
#include <stdexcept>

void Priority_Queue::heapify(int i)
{
    while(i>0)
    {
        int p=parent(i);
        if(p<0) return;
        if(arr[i]<arr[p])
        {
            std::swap(arr[i],arr[p]);
            i=p;
        }else
        {
            return;
        }
    }
}

void Priority_Queue::heapify_down()
{
    int i = 0;
    while(i < size)
    {
        int smallest = i;
        int l = left(i);
        int r = right(i);  
        // Check left child
        if(l < size && arr[l] < arr[smallest])
        {
            smallest = l;
        }
        // Check right child
        if(r < size && arr[r] < arr[smallest])
        {
            smallest = r;
        }
        // If smallest is still i, we're done
        if(smallest == i)
        {
            return;
        }
        // Swap and continue
        std::swap(arr[i], arr[smallest]);
        i = smallest;
    }
}

Priority_Queue::Priority_Queue():size(0)
{
    cap=1000;
    arr = new int[cap];
}

Priority_Queue::~Priority_Queue()
{
    delete []arr;
}

int Priority_Queue::parent(int key)
{
    return (key-1)/2;
}

int Priority_Queue::left(int key)
{
    return 2*key+1;
}

int Priority_Queue::right(int key)
{
    return 2*key+2;
}

void Priority_Queue::insert(int val)
{
    arr[size]=val;
    heapify(size);
    size++;
    if(size>=cap)
    {
        resize();
    }
}

int Priority_Queue::pop()
{
    if(size == 0)
    {
        throw std::out_of_range("Priority queue is empty");
    }
    int temp = arr[0];
    std::swap(arr[0],arr[size-1]);
    size--;
    if(size > 0)  // Only heapify if elements remain
    {
        heapify_down();  // Added: was missing
    }
    return temp;
}

int Priority_Queue::top()
{
    if(size == 0)
    {
        throw std::out_of_range("Priority queue is empty");
    }
    return arr[0];
}

void Priority_Queue::resize()
{
    int *arr2 = new int[2*cap];
    for(int i=0;i<cap;i++)
    {
        arr2[i]=arr[i];
    }
    delete []arr;
    arr=arr2;
    cap=2*cap;
}

bool Priority_Queue::empty() const
{
    return size == 0;
}

int Priority_Queue::get_size() const
{
    return size;
}

