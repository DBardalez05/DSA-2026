#include "Graph.h"
#include "MinPriorityQueue.h"
#include "Dijkstra.h"
#include <cassert>
#include <iostream>
#include <string>

void testGraph() {
    Graph<std::string> graph;
    assert(graph.getVertices().empty());

    //add an edge: both vertices exist, the cost is stored, and it is one-way.
    graph.addEdge("A", "B", 2.0);
    auto vertices = graph.getVertices();
    assert(vertices.size() == 2);
    assert(vertices.count("A") == 1 && vertices.count("B") == 1);
    assert(graph.getEdges("A").at("B") == 2.0);
    assert(graph.getEdges("B").empty());

    //add another neighbor and update an existing edge.
    graph.addEdge("A", "C", 4.0);
    graph.addEdge("A", "B", 7.0);
    auto edges = graph.getEdges("A");
    assert(edges.size() == 2);
    assert(edges.at("B") == 7.0 && edges.at("C") == 4.0);

    //clear then reuse the grpah while not keeping old edges
    graph.clear();
    assert(graph.getVertices().empty());
    graph.addEdge("A", "D", 3.0);
    edges = graph.getEdges("A");
    assert(edges.size() == 1 && edges.at("D") == 3.0);
}

void testMinPriorityQueue() {
    MinPriorityQueue<std::string> queue;

    //empty queue
    assert(queue.isEmpty());
    auto first = queue.next();
    assert(!first.has_value());

    //check if lower priorities come out first, and next() removes entries
    queue.addWithPriority("A", 3.0);
    queue.addWithPriority("B", 1.0);
    queue.addWithPriority("C", 2.0);
    first = queue.next();
    auto second = queue.next();
    auto third = queue.next();
    assert(first.has_value() && first.value() == "B");
    assert(second.has_value() && second.value() == "C");
    assert(third.has_value() && third.value() == "A");
    assert(queue.isEmpty());

    //decrease a priority, then increase another remaining priority.
    queue.addWithPriority("A", 5.0);
    queue.addWithPriority("B", 10.0);
    queue.addWithPriority("C", 7.0);
    queue.adjustPriority("B", 1.0);
    first = queue.next();
    assert(first.has_value() && first.value() == "B");

    queue.adjustPriority("A", 20.0);
    second = queue.next();
    third = queue.next();
    assert(second.has_value() && second.value() == "C");
    assert(third.has_value() && third.value() == "A");
    assert(queue.isEmpty());
}

void testDijkstra() {
    Graph<std::string> graph;
    graph.addEdge("A", "B", 2.0);
    graph.addEdge("B", "D", 3.0);
    graph.addEdge("A", "D", 10.0);

    std::string start = "A";
    std::string destination = "D";

    //check if the indirect route the costs 5, beats the direct edge costing 10
    auto result = dijkstra(graph, start, destination);
    std::vector<std::string> expected = {"A", "B", "D"};
    assert(result.has_value() && result.value() == expected);

    //starting at the destination gives a path containing just that vertex.
    result = dijkstra(graph, start, start);
    expected = {"A"};
    assert(result.has_value() && result.value() == expected);

    //the destination exists but cannot be reached from A.
    graph.addEdge("C", "E", 1.0);
    destination = "E";
    result = dijkstra(graph, start, destination);
    assert(!result.has_value());

    //empty graph.
    graph.clear();
    result = dijkstra(graph, start, destination);
    assert(!result.has_value());
}

int main() {
    testGraph();
    testMinPriorityQueue();
    testDijkstra();
    std::cout << "All tests passed!\n";
    return 0;
}
