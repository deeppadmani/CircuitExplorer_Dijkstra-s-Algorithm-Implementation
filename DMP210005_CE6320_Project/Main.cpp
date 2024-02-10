  #include"DijikstraHeader.h"

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
         
        map<string,int> InputOutputMap;
        map<string,int> InputOutputTypeMap;
        Graph CIRCUIT(CalculateSize(CircuitData));
        string error = "";
        parseCircuit(CircuitData,InputOutputMap,InputOutputTypeMap,CIRCUIT);
        
        
        try
        {
                if(InputOutputTypeMap.end() == InputOutputTypeMap.find(argv[2]))
                        throw "Signal " + (string)argv[2] +" not found in file " + (string)argv[1];
                 if(InputOutputTypeMap.end() == InputOutputTypeMap.find(argv[3]))
                        throw "Signal " + (string)argv[3] +" not found in file " + (string)argv[1];
                else if(INPUTNODE != InputOutputTypeMap[argv[2]])
                        throw "Signal " + (string)argv[2] +" is not an input pin";
                else if(OUTPUTNODE != InputOutputTypeMap[argv[3]])
                        throw "Signal " + (string)argv[3] +" is not an output pin";
        }
        catch (string error)
        {
                 cout << error << endl;
                 return 0;
        }
        string input = (string)argv[2];
        string output = (string)argv[3];
	int ShortestDistance = dijkstra(CIRCUIT,InputOutputMap[input],InputOutputMap[output],InputOutputMap);
        cout << "Minimun Distance from "<< input << " to "<< output << " is : ";
	if(INF != ShortestDistance)
		cout << ShortestDistance << endl;
        else
		cout << "NOT FOUND" << endl;
}


