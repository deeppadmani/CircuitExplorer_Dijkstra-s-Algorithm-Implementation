#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <list> 
#include <set> 
#include <map> 
#include <stack> 

#define INF 9999

using namespace std;

enum Type
{
        INPUTNODE = 0,
        OUTPUTNODE,
        MIDNODENODE,
        MAX_NODE
};

typedef struct  
{
   int destination;
   int Delay;
}NODE;

class Graph
{
        list<NODE>  *adjlist;
        int size;

        public:
        Graph(int size)
        {
              this -> adjlist = new list<NODE>[size];
              this->size = size;  
        }

        void addedge(int source,int destination,int delay);
        void print(map<string,int> &InputOutputMap);
        void CalculateDistance(); 
       
        friend int dijkstra(Graph CIRCUIT, int start, int destination,map<string,int> &InputOutputMap); 
};

void parseCircuit(ifstream &CircuitData,map<string,int> &InputOutputMap,map<string,int> &InputOutputTypeMap,Graph &CIRCUIT);
bool isWhitespace(unsigned char c);
int CalculateSize(ifstream &CircuitData);
bool isCharIsNotNumber(unsigned char c);
string findKeyByValue(const map<std::string, int>& myMap, int valueToFind) ;