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

    // constructor
    Queue(){
        val = new T[size];
        //Needs extra init
    }
    
    // destructor
    ~Queue(){
        delete[] val;
    }

    // input data
    void push(T value){
        
    }

    // change Front
    void pop(){
        
    }

    // check its empty or not
    bool empty(){
        
    }

    // check queue is full or not
    bool isFull(){
        
    }
};

#endif
