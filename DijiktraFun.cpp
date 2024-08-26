#include"DijikstraHeader.h"

int dijkstra(Graph CIRCUIT, int start, int destination, map<string,int> &InputOutputMap) 
{
    int GSize = CIRCUIT.size;
    int dist[GSize];
    int shortestPath[GSize];
    
    for (int node = 0; node < GSize; node++) 
    {
        dist[node] = INF;
        shortestPath[node] = -1; 
    }
    
    dist[start] = 0;     
    list<int> nodeQ;
    set<int> nodeS;
    
    for (int node = 0; node < GSize; node++) 
    {
        nodeQ.push_back(node); 
    }

    while (!nodeQ.empty()) 
    {
        list<int>::iterator MinNodeOfQ = min_element(nodeQ.begin(), nodeQ.end());
        int MinEleOfQ = *MinNodeOfQ; 
        nodeQ.erase(MinNodeOfQ);
        nodeS.insert(MinEleOfQ);
        
        list<NODE>::iterator it;
        for (it = CIRCUIT.adjlist[MinEleOfQ].begin(); it != CIRCUIT.adjlist[MinEleOfQ].end(); it++) 
        {
            if (nodeS.find(it->destination) == nodeS.end()) 
            {
                  if ((dist[MinEleOfQ] + (it->Delay)) < dist[it->destination]) 
                  { 
                      dist[it->destination] = (dist[MinEleOfQ] + (it->Delay));
                      shortestPath[it->destination] = MinEleOfQ;
                  }
            }
        }
    }
    
    if(INF == dist[destination])
    {
          cout << "Shortest path from " << findKeyByValue(InputOutputMap,start) << " to " << findKeyByValue(InputOutputMap,destination) << " is: NOT FOUND"<< endl ;
          return dist[destination];
    }      
    cout << "Shortest path from " << findKeyByValue(InputOutputMap,start) << " to " << findKeyByValue(InputOutputMap,destination) << " is: ";
    int current = destination;
    stack<int> path;

    while (current != start) {
        path.push(current);
        current = shortestPath[current];
    }
    path.push(start);

    while (!path.empty()) {
        cout << " --> " << findKeyByValue(InputOutputMap,path.top());
        path.pop();
    }
    cout << endl;
    

    return dist[destination]; 
}

string findKeyByValue(const map<std::string, int>& myMap, int valueToFind) 
{
    for (const auto& pair : myMap) 
    {
        if (pair.second == valueToFind) 
        {
            return pair.first;
        }
    }
    return ""; 
}
