#include"DijikstraHeader.h"

int CalculateSize(ifstream &CircuitData)
{
        string line;
        int cnt = 0;
        int InputgateCount=0,OutputgateCount=0,InterirorgateCount=0;
        while(getline(CircuitData, line))
        {
                line.erase(remove_if(line.begin(), line.end(), isWhitespace), line.end()); 
                if(-1 != line.find("inputgates"))
                {
                        line.erase(remove_if(line.begin(), line.end(), isCharIsNotNumber), line.end());
                        InputgateCount = stoi(line);
                        cnt++;

                }
                if(-1 != line.find("outputgates"))
                {
                        line.erase(remove_if(line.begin(), line.end(), isCharIsNotNumber), line.end());
                        OutputgateCount = stoi(line);
                        cnt++;
                }
                if(-1 != line.find("interiorgateoutputs"))
                {
                        line.erase(remove_if(line.begin(), line.end(), isCharIsNotNumber), line.end());
                        InterirorgateCount = stoi(line);
                        cnt++;
                }
                if (3==cnt)
                    break;
        }
        return (InputgateCount + OutputgateCount + InterirorgateCount);
}

void parseCircuit(ifstream &CircuitData,map<string,int> &InputOutputMap,map<string,int> &InputOutputTypeMap,Graph &CIRCUIT)
{
        string line;
        string result;
        int NodeIndex=0;
        int GIdx;
        set<string> OUTPUT;
        set<string> INPUT;
        
        while(getline(CircuitData, line))
        {
                if(-1 != line.find("INPUT"))
                {
                   size_t startPos = line.find("(");
                   size_t lengthToRemove = startPos + 1;
                   result = line.substr(lengthToRemove, line.length() - lengthToRemove - 1);
                   InputOutputMap.insert({result,NodeIndex});
                   InputOutputTypeMap.insert({result,INPUTNODE});
                   INPUT.insert(result);
                   NodeIndex++;
                }
                 
                if(-1 != line.find("OUTPUT"))
                {
                   size_t startPos = line.find("(");
                   size_t lengthToRemove = startPos + 1;
                   result = line.substr(lengthToRemove, line.length() - lengthToRemove - 1);
                   OUTPUT.insert(result);
                }

                if((-1 != line.find("=")) && (-1 == line.find("#")))
                {
                   string midgate;
                   string midGateInput;
                   line.erase(remove_if(line.begin(), line.end(), isWhitespace), line.end()); 
                   size_t equalIdx = line.find("=");
                   midgate = line.substr(0, equalIdx);
                   if(INPUT.end() == INPUT.find(midgate) && (OUTPUT.end() == OUTPUT.find(midgate)))
                   {
                        InputOutputMap.insert({midgate,NodeIndex});
                        InputOutputTypeMap.insert({midgate,MIDNODENODE});
                        NodeIndex++;
                   }
                   else if(OUTPUT.end() != OUTPUT.find(midgate))
                   {
                        InputOutputMap.insert({midgate,NodeIndex});
                        InputOutputTypeMap.insert({midgate,OUTPUTNODE});
                        NodeIndex++;
                   }
                   size_t startPos = line.find("(");
                   size_t lengthToRemove = startPos + 1;
                   result = line.substr(lengthToRemove, line.length() - lengthToRemove - 1);
                   
                   stringstream midGateInputsStr(result);
                   while (getline(midGateInputsStr, midGateInput, ','))
                   {
                        CIRCUIT.addedge(InputOutputMap[midGateInput],InputOutputMap[midgate],INF);
                   }
                }
        }
        
        CIRCUIT.CalculateDistance();
   //     CIRCUIT.print(InputOutputMap);
}



bool isWhitespace(unsigned char c) 
{
        if (c == ' ' || c == '\t' || c == '\n' ||
            c == '\r' || c == '\f' || c == '\v') 
        {
          return true;
        } 
        else 
        {
          return false;
        }
}

bool isCharIsNotNumber(unsigned char c) 
{
    if (c >= '0' && c <= '9') 
    {
        return false;
    } 
    else 
    {
        return true;
    }
}
