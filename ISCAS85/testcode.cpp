#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <list> 
#include <set> 
#define INF 9999999

using namespace std;

enum Type
{
        INPUTNODE = 0,
        OUTPUTNODE,
        MIDNODENODE,
        MAX_NODE
};
        
class CircuitNode
{
        public:
        string name;
        int type;
        int distance;
        int index;
        //class CircuitNode *next;
        
        CircuitNode(string name,int type,int distance,int index)
        {
                this->name = name;
                this->type = type;
                this->distance = distance;
                this -> index = index;
        }
        void printNode()
        {
                //cout << "Index : " << this -> index << "Name : " << this->name << "Type : " << this->type << "Distance : " << this->distance << endl;
                cout << this -> index << " : " << this->name << "--"<< this -> distance << "|-->" ;
        }
};

class Graph
{
        list<CircuitNode>  *adjlist;
        int size;
        public:
        Graph(int size)
        {
              adjlist = new list<CircuitNode>[size];
              this->size = size;  
              cout << "Graph Size : " << size << endl; 
        }

        void addedge(int index,CircuitNode gatein)
        {
                adjlist[index].push_back(gatein);
        }

        void print()
        {
                for(int Idx=0;Idx<size;Idx++)
                {
                        cout << Idx << "--> ";
                        for (list<CircuitNode>::iterator it = adjlist[Idx].begin();it != adjlist[Idx].end();it++)
                        {
                                it->printNode();
                        }
                        cout << endl;
                }
                cout << endl;
        }

       int findNode(const string& midgate) 
       {
                for(int Idx=0;Idx<size;Idx++)
                {
                        for (list<CircuitNode>::iterator it = adjlist[Idx].begin();it != adjlist[Idx].end();it++)
                        {
                                if(it->name == midgate  &&  it->type != MAX_NODE)
                                {
                                //        cout << "FindNode : " << Idx << endl;
                                        return Idx;
                                }
                        }
                }
                return -1;
       }
       void CalculateDistance() 
       {
                for(int Idx=0;Idx<size;Idx++)
                {
                        list<CircuitNode>::iterator it = adjlist[Idx].begin();
                        if(it->type == MIDNODENODE)
                                it -> distance =  adjlist[Idx].size() - 1;
                }
       }
};

void parseCircuit(ifstream &CircuitData,set<string> &INPUT,set<string> &OUTPUT,set<string> &MIDNODE,Graph &CIRCUIT);
bool isWhitespace(unsigned char c);
int CalculateSize(ifstream &CircuitData);
bool isCharIsNotNumber(unsigned char c);

   int main(int argc, char **argv)
   {
        
        if(4 != argc)
        {
                cout << "Incorrect number of arguments" << endl;
                return 0;
        }       
        ifstream CircuitData;
         
        try
        {
                 CircuitData.open(argv[1]);
                 if(!(CircuitData.is_open()))
                         throw (string)argv[1];
        }
        catch (string filename)
        {
                 cout << "Wrong file name : " << filename << endl;
                 return 0;
        }
         
        set<string> INPUT;
        set<string> OUTPUT;
        set<string> MIDNODE;
        
        Graph CIRCUIT(CalculateSize(CircuitData));
        string error = "";
        parseCircuit(CircuitData,INPUT,OUTPUT,MIDNODE,CIRCUIT);
        
        try
        {
                if((INPUT.end() == INPUT.find(argv[2])) && OUTPUT.end() == OUTPUT.find(argv[2]))
                        throw "Signal " + (string)argv[2] +" not found in file " + (string)argv[1];
                else if(OUTPUT.end() != OUTPUT.find(argv[2]))
                        throw "Signal " + (string)argv[2] +" is not an input pin";

                if (OUTPUT.end() == OUTPUT.find(argv[3]) && INPUT.end() == INPUT.find(argv[3]))
                        throw "Signal " + (string)argv[3] +" not found in file " + (string)argv[1];
                else if(INPUT.end() != INPUT.find(argv[3]))
                        throw "Signal " + (string)argv[3] +" is not an output pin";
        }
        catch (string error)
        {
                 cout << error << endl;
        }
}

int CalculateSize(ifstream &CircuitData)
{
        string line;
        int InputgateCount=0,OutputgateCount=0,InterirorgateCount=0;
        while(getline(CircuitData, line))
        {
                line.erase(remove_if(line.begin(), line.end(), isWhitespace), line.end()); 
                if(-1 != line.find("inputgates"))
                {
                        line.erase(remove_if(line.begin(), line.end(), isCharIsNotNumber), line.end());
                        InputgateCount = stoi(line);
                        cout << "InputgateCount : "<< InputgateCount <<endl;

                }
                if(-1 != line.find("outputgates"))
                {
                        line.erase(remove_if(line.begin(), line.end(), isCharIsNotNumber), line.end());
                        OutputgateCount = stoi(line);
                        cout << "OutputgateCount : "<< OutputgateCount <<endl;
                }
                if(-1 != line.find("interiorgateoutputs"))
                {
                        line.erase(remove_if(line.begin(), line.end(), isCharIsNotNumber), line.end());
                        InterirorgateCount = stoi(line);
                        cout << "InterirorgateCount : "<< InterirorgateCount <<endl;
                        break;
                }
        }
        return (InputgateCount + OutputgateCount + InterirorgateCount);
}

void parseCircuit(ifstream &CircuitData,set<string> &INPUT,set<string> &OUTPUT,set<string> &MIDNODE,Graph &CIRCUIT)
{
        string line;
        string result;
        int NodeIndex=0;
        int GIdx;
        while(getline(CircuitData, line))
        {
                if(-1 != line.find("INPUT"))
                {
                   size_t startPos = line.find("(");
                   size_t lengthToRemove = startPos + 1;
                   result = line.substr(lengthToRemove, line.length() - lengthToRemove - 1);
                   INPUT.insert(result);
                   CircuitNode NewNode(result,INPUTNODE,0,NodeIndex);
                   NewNode.printNode();
                   CIRCUIT.addedge(NodeIndex,NewNode);
                   cout << "Done" << endl;
                   NodeIndex++;
                }
                 
                if(-1 != line.find("OUTPUT"))
                {
                   size_t startPos = line.find("(");
                   size_t lengthToRemove = startPos + 1;
                   result = line.substr(lengthToRemove, line.length() - lengthToRemove - 1);
                   OUTPUT.insert(result);
                   CircuitNode NewNode(result,OUTPUTNODE,1,NodeIndex);
                   NewNode.printNode();
                   CIRCUIT.addedge(NodeIndex,NewNode);
                   NodeIndex++;
                }
                if((-1 != line.find("=")) && (-1 == line.find("#")))
                {
                   string midgate;
                   string midGateInput;
                   line.erase(remove_if(line.begin(), line.end(), isWhitespace), line.end()); 
                   size_t equalIdx = line.find("=");
                   midgate = line.substr(0, equalIdx);
                   if((INPUT.end() == INPUT.find(midgate)) && ((OUTPUT.end() == OUTPUT.find(midgate))))
                   {
                        CircuitNode NewNode(midgate,MIDNODENODE,INF,NodeIndex);
                        NewNode.printNode();
                        CIRCUIT.addedge(NodeIndex,NewNode);
                        NodeIndex++;
                   }
                   size_t startPos = line.find("(");
                   size_t lengthToRemove = startPos + 1;
                   result = line.substr(lengthToRemove, line.length() - lengthToRemove - 1);
                      //  cout << result << endl;
                   stringstream midGateInputsStr(result);
                   while (getline(midGateInputsStr, midGateInput, ','))
                   {
                        int tempIdx = 0;
                        GIdx = CIRCUIT.findNode(midGateInput);
                       // tempIdx = (-1 != GIdx)? GIdx:NodeIndex;
                        CircuitNode NewNode(midgate,MAX_NODE,INF,GIdx);
                        NewNode.printNode();
                        CIRCUIT.addedge(GIdx,NewNode);
                        
                   }
                   cout << "Done " << NodeIndex << endl;
                }
        }
        
        CIRCUIT.CalculateDistance();
        CIRCUIT.print();
}

bool isWhitespace(unsigned char c) {
    if (c == ' ' || c == '\t' || c == '\n' ||
        c == '\r' || c == '\f' || c == '\v') {
        return true;
    } else {
        return false;
    }
}

bool isCharIsNotNumber(unsigned char c) {
    if (c >= '0' && c <= '9') {
        return false;
    } else {
        return true;
    }
}

