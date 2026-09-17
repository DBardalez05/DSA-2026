#pragma once
#include "LinkedList.h"

template <typename T>
struct Queue{
    double_linked_list<T> items;

    /** Adds data to the end of the queue.
     * @param data The value to add.
     */
    void enqueue(T value){
        items.pushFront(value);
    }

    /** Removes the front element. An empty queue stays unchanged.
     * @return The front value, or std::nullopt if the queue is empty.
     */
    std::optional<T> dequeue(){
        return items.popBack();
    }

    /** Looks at the front element without removing it.
     * @return The front value, or std::nullopt if the queue is empty.
     */
    std::optional<T> peek(){
        return items.peekBack();
    }

    /** @return true if the queue is empty, false otherwise. */
    bool isEmpty(){
        return items.isEmpty();
    }
};