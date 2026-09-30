#include <Graph.h>
#include <MinPriorityQueue.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

template <typename T>

std::optional<std::vector<T>> dijkstra(Graph<T>& graph, T start, T destination){
    std::unordered_map<T, double> distance;
    std::unordered_map<T, T> previous;
    MinPriorityQueue<T> queue;

    if (graph.getVertices().empty() == true){
        return std::nullopt;
    }

    distance{start} = 0.0;
    queue.addWithPriority(start, 0.0);

    while(queue.isEmpty() != true){
        T temp = queue.next().value();
        std::unordered_map<T, double> temp_edges;
        temp_edges = getEdges(temp);
        for(auto edge : temp_edges){
            queue.addWithPriority(edge.first, edge.second);
            distance{edge.first} = edge.second;
        }
    }

};
