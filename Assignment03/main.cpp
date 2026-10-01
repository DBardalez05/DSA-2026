#include "Dijkstra.h"
#include <iostream>
#include <string>

//in here we call the Dijkstra function and get it to print out route and cost
void printRoute(Graph<std::string>& graph, std::string start, std::string destination) {
    auto result = dijkstra(graph, start, destination);
    std::cout << start << " to " << destination << ": ";

    //if the function fails it returns std::nullopt and has no value so we know that no route was found
    if (!result.has_value()) {
        std::cout << "No route found\n";
        return;
    }
    auto path = result.value();
    double totalCost = 0.0;

    //we must get data from all of the elements that the path went through to print final statement and get cost
    for (std::size_t i = 0; i < path.size(); ++i) {
        std::cout << path[i];

        if (i + 1 < path.size()) {
            std::cout << " -> ";
            //find the cost from this city to the next city.
            auto neighbors = graph.getEdges(path[i]);
            totalCost += neighbors[path[i + 1]];
        }
    }
    //print final statemenbt
    std::cout << " | Total cost: $" << totalCost << "\n";
}

int main() {
    Graph<std::string> graph;
    //add edges or random cities and give them a cost
    graph.addEdge("Boston", "Providence", 20.0);
    graph.addEdge("Providence", "New York", 40.0);
    graph.addEdge("Boston", "New York", 90.0);
    graph.addEdge("New York", "Philadelphia", 30.0);
    graph.addEdge("Providence", "Philadelphia", 100.0);
    graph.addEdge("Philadelphia", "Washington, DC", 35.0);
    graph.addEdge("New York", "Washington, DC", 100.0);
    graph.addEdge("Boston", "Washington, DC", 250.0);

    printRoute(graph, "Boston", "Washington, DC");
    printRoute(graph, "Providence", "Philadelphia");
    printRoute(graph, "Boston", "New York");
    printRoute(graph, "Washington, DC", "Boston");

    return 0;
}