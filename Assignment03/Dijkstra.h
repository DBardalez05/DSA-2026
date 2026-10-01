#include <Graph.h>
#include <MinPriorityQueue.h>

template <typename T>

//finds a lowest-cost path from start to destination.
//returns the path vertices, or std::nullopt if no route exists.
//assumes all edge weights are nonnegative.
std::optional<std::vector<T>> dijkstra(Graph<T>& graph, T start, T destination){
    //maps and queues to hold temporary values of where edges are in relation to other edges 
    std::unordered_map<T, double> distance;
    std::unordered_map<T, T> previous;
    MinPriorityQueue<T> queue;

    //first we check if the graph object we are going to look in even has edges and verticies to work with, return nothing if not
    if (graph.getVertices().empty() == true){
        return std::nullopt;
    }
    //then we have to check if the start node is within the list of verticies of our graph object, or else return nothing
    int test = 0;
    std::unordered_set<T> temp_sc = graph.getVertices();
    for(auto vert : temp_sc){
        if(vert == start){
            test = 1;
            break;
        }
    }
    if (test == 0){
        return std::nullopt;
    }

    //set distance and add to queue the start element
    distance[start] = 0.0;
    queue.addWithPriority(start, 0.0);

    //Once the queue is empty we now know that all of the verticies and edges have been explored
    while(queue.isEmpty() != true){
        T temp = queue.next().value();
        //Once we get to the desired location then end the loop
        if(temp == destination){
            break;
        }
        std::unordered_map<T, double> temp_edges;
        temp_edges = graph.getEdges(temp);
        //as we look throuhg the edges that are children to the cirrent edge we on we keep adding teh cost as we have not gotten to destination
        for(auto edge : temp_edges){
            if(distance.count(edge.first) == 0 || distance[edge.first] > distance[temp] + edge.second){ //count measures if the distance to this node is on teh map yet if not then we must give it one
            //important to check first that it is empty or elses can chane map and add soemthign with distance of 0 which is wrong
                distance[edge.first] = distance[temp] + edge.second;
                queue.addWithPriority(edge.first, distance[edge.first]);
                previous[edge.first]  = temp;
                
            }
        }
        
    }
    //we now look throuhg all elements in distance and see if the destination is there if not that means we didnt reach our destination and must return nothing.
    int temp_check = 0;
    T temp_start = {};
    for(auto dis: distance){
        if (dis.first == destination){
            temp_start = dis.first;
            temp_check = 1;
            break;
        }
    }
    if (temp_check == 0){
        return std::nullopt;
    }

    //remmeber that at this point temp start has the name of the element so no need to .first when trying to index anem of element
    std::vector<T> origin = {};
    origin.push_back(temp_start);
    while (temp_start != start){
        origin.push_back(previous[temp_start]);
        temp_start = previous[temp_start];
    }
    //reverse edits teh existing vector (void)
    std::reverse(origin.begin(),origin.end());
    return origin;

};
