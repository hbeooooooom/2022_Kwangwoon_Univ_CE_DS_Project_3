#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif

template<class T> class Queue
{
public:
    int front;
    int rear;
    int size; //Free to define (recommand 100 or 200)
    T *val;

    Queue(){
        size = 200;
        val = new T[size];
        front = 0;
        rear = 0;
    }
    ~Queue()
    {
        delete[] val;
    }

    void push(T value) {
        if(!isFull() || rear <= size)
        {
            val[rear] = value;
            rear++;
        }
    }

    void pop() {
        if(!empty())
        {
            front++;
        }
    }

    bool empty() {
        if(front == rear)
            return true;
        return false;
    }

    bool isFull() {
        if(rear > size)
            return true;
        return false;
    }
};


#endif
