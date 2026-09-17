#pragma once
#include <optional> // new data type I learned wher it can hold any data type of T or nothing


template <typename T>
struct Node{
    T value = {};
    Node<T>* next_node = nullptr;
    Node<T>* prev_node = nullptr;
};



template <typename T> // I jsut learned this and seems really useful if you dont know what datat type the object will be.
struct double_linked_list {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr; 

    /** @return true if the list is empty, false otherwise. */
    bool isEmpty(){
        if (head == nullptr)
        {
            return true;
        }
        return false;
    }

    /** Adds data to the front of the linked list.
     * @param data The value to add.
     */
    void pushFront(T data){
        Node<T>* new_node = new Node<T>{data, nullptr, nullptr};
        if (head == nullptr){
            head = new_node;
            tail = new_node;
        }
        else{//next node is the current head but then we set that nodes previous node as the new node and then we set the head to the new node.
            new_node ->next_node = head;
            head ->prev_node = new_node;
            head = new_node;
        }
    }

    /** Adds data to the back of the linked list.
     * @param data The value to add.
     */
    void pushBack(T data){
        Node<T>* new_node = new Node<T>{data, nullptr, nullptr};
        if (head == nullptr){
            head = new_node;
            tail = new_node;
        }
        else{
            new_node ->prev_node = tail;
            tail ->next_node = new_node;
            tail = new_node;
        }
    }

    /** Looks at the front element without removing it.
     * @return The front value, or std::nullopt if the list is empty.
     */
    std::optional<T> peekFront(){
        if (head == nullptr){
            return std::nullopt;//This basically means that there is nothing to return.
        }
        else{
            return head ->value;
        }

    }   

    /** Looks at the back element without removing it.
     * @return The back value, or std::nullopt if the list is empty.
     */
    std::optional<T> peekBack(){
        if (tail == nullptr){
            return std::nullopt;
        }
        else{
            return tail ->value;
        }

    }

    
    /** Removes the front element. An empty list stays unchanged.
     * @return The front value, or std::nullopt if the list is empty.
     */
    std::optional<T> popFront(){
    if (head == nullptr){
        return std::nullopt;
    }
    else if (head ->next_node == nullptr){
        T value = head ->value;
        delete head;
        head = nullptr;
        tail = nullptr;
        return value;
    }
    else{
        Node<T>* old_head = head;
        T value = old_head ->value;
        head = head ->next_node;
        head ->prev_node = nullptr;
        delete old_head;
        return value;

    }
    }

    /** Removes the back element. An empty list stays unchanged.
     * @return The back value, or std::nullopt if the list is empty.
     */
    std::optional<T> popBack(){
    if (tail == nullptr){
        return std::nullopt;
    }
    else if (tail ->prev_node == nullptr){
        T value = tail ->value;
        delete tail;
        head = nullptr;
        tail = nullptr;
        return value;
    }
    else{
        Node<T>* old_tail = tail;
        T value = old_tail ->value;
        tail = tail ->prev_node;
        tail ->next_node = nullptr;
        delete old_tail;
        return value;

    }
    }

};

