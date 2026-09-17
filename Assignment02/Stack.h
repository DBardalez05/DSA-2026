#pragma once
#include "LinkedList.h"

template <typename T>
struct Stack{
    double_linked_list<T> items;

    /** Adds data to the top of the stack.
     * @param data The value to add.
     */
    void push(T value){
        items.pushFront(value);
    }

    /** Removes the top element. An empty stack stays unchanged.
     * @return The top value, or std::nullopt if the stack is empty.
     */
    std::optional<T> pop(){
        return items.popFront();
    }

    /** Looks at the top element without removing it.
     * @return The top value, or std::nullopt if the stack is empty.
     */
    std::optional<T> peek(){
        return items.peekFront();
    }

    /** @return true if the stack is empty, false otherwise. */
    bool isEmpty(){
        return items.isEmpty();
    }

};


