#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Stack
{
private:
    class StackNode
    {
    public:
        T Data;
        StackNode* pNext;

        StackNode(T data) : Data(data), pNext(NULL) {}
    };

private:
    // the head pointer of the stack and queue
    StackNode* m_pTop;

public:
    // constructor
    Stack(){

    }

    // destructor
    ~Stack(){

    }

    // push the data into this stack and queue
    void Push(T data){

    }

    // pop(remove) the last-in data from this stack and queue
    void Pop(){

    }

    // get the last-in data of this stack and queue and returnthe last-in data of this stack and queue
    T Top(){

    }

    // check whether this stack and queue is empty or not and return true if this stack and queue is empty. false otherwise.
    bool IsEmpty(){

    }
};

#endif
