#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>

template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;

public:
    MinHeap() {}

    // insert key-value pair / key: the key that is used for sorting, value: the value that is managed in this heap
    void Push(TKey key, TValue value){

    }
    
    // remove the minimum element
    void Pop(){

    }

    // get the minimum element and return the minimum element
    std::pair<TKey, TValue> Top(){

    }

    // get the key-value pair which the value is the same as the target and return the key-value pair which the value is the same as the target
    std::pair<TKey, TValue> Get(TValue target){

    }
    
    // check whether this heap is empty or not and return true if this heap is empty
    bool IsEmpty(){

    }

    // change the key of the node which the value is the target. In general, the newKey should be smaller than the old key. / target: the target to change the key, newKey: new key for the target
    void DecKey(TValue target, TKey newKey){

    }

private:
    // heap-sort, heapify.this function can be called recursively
    void Heapify(int index){
        
    }
};

#endif
