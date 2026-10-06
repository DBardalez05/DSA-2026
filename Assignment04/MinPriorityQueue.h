#pragma once
#include <optional>
#include <vector>
#include <algorithm>

template <typename T>
struct QueueEntry{
    T element = {};
    double priority = {};
};


/**
 * ``MinPriorityQueue`` maintains a priority queue where the lower
 *  the priority value, the sooner the element will be removed from
 *  the queue.
 *  @param T the representation of the items in the queue
 */

template <typename T>
struct MinPriorityQueue{
    std::vector<QueueEntry<T>> mp_queue{};

    static bool comparePriority(const QueueEntry<T>& first,
                            const QueueEntry<T>& second) {
    return first.priority > second.priority;
}

    /**
     * @return true if the queue is empty, false otherwise
     */

    bool isEmpty(){
        bool temp = mp_queue.empty();
        return temp;
    }

    /**
     * Add [elem] with at level [priority]
     */
    
    void addWithPriority(T element, double priority){
        mp_queue.push_back(QueueEntry<T>{element, priority});
        std::push_heap(mp_queue.begin(), mp_queue.end(), comparePriority);
    }

    /**
     * Get the next (highest priority) element and remove this element from the queue.
     * @return the next element in terms of priority.  If empty, return null.
     */
    
    std::optional<T> next(){
        if (isEmpty() == true){
            return std::nullopt;
        }
        std::pop_heap(mp_queue.begin(),mp_queue.end(),comparePriority);
        T temp = mp_queue.back().element;
        mp_queue.pop_back();
        return temp;    
    }

    /**
     * Adjust the priority of the given element
     * @param elem whose priority should change
     * @param newPriority the priority to use for the element
     *   the lower the priority the earlier the element int
     *   the order.
     */
    
    void adjustPriority(T elem, double new_priority){
        for(std::size_t i = 0; i < mp_queue.size(); i++){
            if (mp_queue[i].element == elem){
                mp_queue[i].priority = new_priority;
                break;
            }
        }
        std::make_heap(mp_queue.begin(),mp_queue.end(),comparePriority);
    }



};
