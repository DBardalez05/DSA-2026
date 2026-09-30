#pragma once
#include <unordered_map>
#include <unordered_set>

template <typename T>
class Graph{
    std::unordered_set<T> vertices;
    std::unordered_map<T, std::unordered_map<T, double>> adjacency_list;

public:
    void addEdge(T from, T to, double cost){
        vertices.insert(from);
        verticies.insert(to);
        ajacency_list[from][to] = cost;

    }

    std::unordered_set<T> getVertices(){
        return vertices;
    }

    std::unordered_map<T, double> getEdges(T from) {
        std::unordered_map<T, double> temp;
        temp = adjacency_list[from];
        return temp;
    }

    void clear(){
        vertices.clear();
        adjacency_list.clear();
    }

};
