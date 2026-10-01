#pragma once
#include <unordered_map>
#include <unordered_set>

template <typename T>


/**
 * ``Graph`` represents a directed graph
 * @param VertexType the type that represents a vertex in the graph
 */
class Graph{
    std::unordered_set<T> vertices;
    std::unordered_map<T, std::unordered_map<T, double>> adjacency_list;

public:
    
    /**
     * Add an edge between [from] and [to] with edge weight [cost]
     */
    void addEdge(T from, T to, double cost){
        vertices.insert(from);
        vertices.insert(to);
        adjacency_list[from][to] = cost;

    }

    /**
     * @return the vertices in the graph
     */
    std::unordered_set<T> getVertices(){
        return vertices;
    }

    /**
     * Get all the edges that begin at [from]
     * @return a map where each key represents a vertex connected to [from] and the value represents the edge weight.
     */
    std::unordered_map<T, double> getEdges(T from) {
        std::unordered_map<T, double> temp;
        temp = adjacency_list[from];
        return temp;
    }

    /**
     * Remove all edges and vertices from the graph
     */
    void clear(){
        vertices.clear();
        adjacency_list.clear();
    }

};
