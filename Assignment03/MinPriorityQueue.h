#pragma once
#include <optional>
#include <vector>
#include <algorithm>

template <typename T>
struct QueueEntry{
    T element = {};
    double priority = {};
};

template <typename T>
struct MinPriorityQueue{
    std::vector<QueueEntry<T>> mp_queue{};

    static bool comparePriority(const QueueEntry<T>& first,
                            const QueueEntry<T>& second) {
    return first.priority > second.priority;
}

    bool isEmpty(){
        bool temp = mp_queue.empty();
        return temp;
    }

    void addWithPriority(T element, double priority){
        mp_queue.push_back(QueueEntry<T>{element, priority});
        std::push_heap(mp_queue.begin(), mp_queue.end(), comparePriority)
    }

    std::optional<T> next(){
        if (isEmpty() == true){
            return std::nullopt;
        }
        std::pop_heap(mp_queue.begin(),mp_queue.end(),comparePriority);
        T temp = mp_queue.back().element;
        mp_queue.pop_back();
        return temp;    
    }

    void adjustPriority(T elem, double new_priority){
        for(std::size_t i = 0, i < mp_queue.size(), i++){
            if (mp_queue[i].element == elem){
                mp_queue[i].priority = new_priority;
                break;
            }
        }
        std::make_heap(mp_queue.begin(),mp_queue.end(),comparePriority);
    }



};
