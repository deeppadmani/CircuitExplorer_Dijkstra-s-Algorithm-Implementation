#include"DijikstraHeader.h"


void Graph::addedge(int source,int destination,int delay)
{
          NODE newNode;
          newNode.destination = destination;
          newNode.Delay = delay;

          adjlist[source].push_back(newNode);
}

void Graph::print(map<string,int> &InputOutputMap)
{
     for(int Idx=0;Idx<size;Idx++)
     {
            cout << findKeyByValue(InputOutputMap,Idx);
            for (list<NODE>::iterator it = adjlist[Idx].begin();it != adjlist[Idx].end();it++)
            {
                    cout << "--> " <<findKeyByValue(InputOutputMap,it->destination)  << "|" << it -> Delay;
                    
            }
            cout << endl;
     }
     cout << endl;
}

void Graph::CalculateDistance() 
{
        int delay = INF;
        for(int Idx=0;Idx<size;Idx++)
        {
                list<NODE>::iterator it = adjlist[Idx].begin();
                delay =  adjlist[Idx].size();
                for(;it != adjlist[Idx].end();it++)
                {
                   if(INF == it -> Delay)
                        it -> Delay = delay;
                }
        }
}