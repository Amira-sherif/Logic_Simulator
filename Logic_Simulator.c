#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

class  Node
{
private:
    std::string mName; 
    int mValue;    

public:

    Node():mName(""),mValue(0){}

    Node(std::string name):mName(name),mValue(0){}

    Node(std::string name, int value):mName(name),mValue(value){}

    void setname(std::string name)
    {    mName = name; }

    void setvalue(int value)
    {    mValue = value; }

    std::string getname()
    { return mName; }

    int getvalue()
    { return mValue; }
};

class  Gate
{
    
protected:
    Node* mFirstInput;  
    Node* mSecondInput; 
    Node* mOut;    
    
public:

    Gate():mFirstInput(nullptr),mSecondInput(nullptr),mOut(nullptr){}
    
    ~Gate(){}
    
    void set_in1(Node* FirstInput)
    {mFirstInput = FirstInput;}

    void set_in2(Node* SecondInput)
    {mSecondInput = SecondInput;}

    void set_out(Node* Out)
    {mOut = Out;}

    Node* get_in1()
    {return mFirstInput;}

    Node* get_in2()
    {return mSecondInput;}
    
    Node* get_out()
    {return mOut;}

    virtual void Calculate_Out() = 0;
    
};

class and_gate : public Gate
{
public:
    
    void Calculate_Out(){
    if (mFirstInput->getvalue() == 1 && mSecondInput->getvalue() == 1)
        mOut->setvalue(1);

    else
        mOut->setvalue(0);}
};

class  or_gate :public Gate
{
public:
    void Calculate_Out(){
    if (mFirstInput->getvalue() == 0 && mSecondInput->getvalue() == 0)
        mOut->setvalue(0);

    else
        mOut->setvalue(1);}
};

class  nand_gate:public Gate
{
    public:
       void Calculate_Out(){

    if (mFirstInput->getvalue() == 1 && mSecondInput->getvalue() == 1)
        mOut->setvalue(0);

    else
        mOut->setvalue(1);}
};

class  nor_gate :public Gate
{
public:
    void Calculate_Out(){
    if (mFirstInput->getvalue() == 0 && mSecondInput->getvalue() == 0)
        mOut->setvalue(1);

    else
        mOut->setvalue(0);}
};

class  xor_gate :public Gate
{
public:
    void Calculate_Out(){
    if (mFirstInput->getvalue() == mSecondInput->getvalue())
        mOut->setvalue(0);

    else
        mOut->setvalue(1);}
};

class  xnor_gate :public Gate
{
public:
    void Calculate_Out(){
    if (mFirstInput->getvalue() == mSecondInput->getvalue())
        mOut->setvalue(1);

    else
        mOut->setvalue(0);}
};

class  not_gate :public Gate
{
public:
    void Calculate_Out(){
    if (mFirstInput->getvalue() == 1)
        mOut->setvalue(0);

    else
        mOut->setvalue(1);}
};

class LogicSimulator {
private:
    std::vector<Node*> mNodes;
    std::vector<Gate*> mGates;
    int mNodeNumber; 
    int mGateNumber; 

public:
    LogicSimulator():mNodes(), mGates(),mNodeNumber(0),mGateNumber(0) {}
    
    ~LogicSimulator(){}

    Node* CreateNode(std::string nodeName){
        auto node = new Node(nodeName);
        mNodes.push_back(node);
        mNodeNumber++;
        return node;}
    
    Node* FindNode(std::string nodeName){
        std::vector<Node*>::iterator found = std::find_if(mNodes.begin(), mNodes.end(), [nodeName](Node* node) {
        return nodeName == node->getname();
        });

        if(found != std::end(mNodes))
            return *found;

        return CreateNode(nodeName);}
    
    Gate* CreateGate(std::string gateName){

    Gate* gate = NULL;

    if (gateName == "AND")
        gate = new and_gate();

    else if (gateName == "NAND")
        gate = new nand_gate();

    else if (gateName == "OR")
        gate = new or_gate();

    else if (gateName == "NOR")
        gate = new nor_gate();

    else if (gateName == "XOR")
        gate = new xor_gate();

    else if (gateName == "XNOR")
        gate = new xnor_gate();

    else if (gateName == "NOT")
        gate = new not_gate();

    else
        return NULL;

    mGates.push_back(gate);
    mGateNumber++;
    return gate;}

//    void StartSimulation();
    void PrintAll(){
        for (auto const& node : mNodes)
            std::cout << "Node name is => " << node->getname() << " Node value is => " << node->getvalue() << "\n";}
};

class Simulator
{
private:
    Node* mNodes[1000];
    Gate* mGates[1000];
    int mNodeSize;
    int mGateSize;

public:
    Simulator()
{
    int i;
    mGateSize = 0;
    mNodeSize = 0;
    for (i = 0; i < GetNode_Size(); i++)
        mNodes[i] = NULL;

    for (i = 0; i < GetGate_Size(); i++)
        mGates[i] = NULL;
}
    virtual ~Simulator()
{
//    int i;

//    for (i = 0; i < GetNode_Size(); i++)
//        delete[] mNodes[i];

//    for (i = 0; i < GetGate_Size(); i++)
//        delete[] mGates[i];
}
    void SetNode_Size(int n)
    {mNodeSize = n;}

    int GetNode_Size()
    {return mNodeSize;}
    
    void SetGate_Size(int n)
    {mGateSize = n;}
    
    int GetGate_Size()
    {return mGateSize;}
    
    Node* Creat_Node(string n)
{
    mNodes[mNodeSize] = new Node(n);
    mNodeSize++;
    return mNodes[mNodeSize - 1];
}

    Node* Find_Node(string n)
{
    for (int i = 0; i < GetNode_Size(); i++)
    {
        if (n == (mNodes[i]->getname())) {
            return mNodes[i];
        }
    }
    return Creat_Node(n);

}
//    Node* Add_Node(string n);
    Gate* Creat_Gate(string n)
    {
    Gate* p = NULL;

    if (n == "AND")
        p = new and_gate();

    else if (n == "NAND")
        p = new nand_gate();

    else if (n == "OR")
        p = new or_gate();

    else if (n == "NOR")
        p = new nor_gate();

    else if (n == "XOR")
        p = new xor_gate();

    else if (n == "XNOR")
        p = new xnor_gate();

    else if (n == "NOT")
        p = new not_gate();

    else
        return NULL;

    mGateSize++;
    mGates[mGateSize - 1] = p;
    return mGates[mGateSize - 1];
}

    void simulate()
{
    for (int i = 0; i < GetGate_Size(); i++)
        mGates[i]->Calculate_Out();
}
    
    void Load(string x)
{
    string word;
    stringstream iss(x);
    
    while ((iss >> word))
       {
        string mNodes;
        mNodes = word;

        if (mNodes == "SET")
        {
            string node;
            int mValue;
            iss >> word;
            node = word;
            iss >> word;
            mValue = stoi(word);
            Find_Node(node)->setvalue(mValue);

        }
        else if (mNodes == "OUT")
        {
            string mOut;
            iss >> word;
            mOut = word;
            if (mOut == "ALL")
                {
                Print_All();
                break;}
            else
                cout <<Find_Node(mOut)->getname() << ": "<< Find_Node(mOut)->getvalue() << endl;
        }

        else if (mNodes == "SIM")
            simulate();

        else {
            Gate* g = Creat_Gate(mNodes);
            string node1, node2, node3;
            iss >> word;
            node1 = word;
            iss >> word;
            node2 = word;
            iss >> word;
            node3 = word;
            g->set_in1(Find_Node(node1));
            g->set_in2(Find_Node(node2));
            g->set_out(Find_Node(node3));
        }
    }
}
    
    void Print_All()
{
    int i;

    for (i = 0; i < GetNode_Size(); i++)
        cout << mNodes[i]->getname() << ": " << mNodes[i]->getvalue() << endl;
}
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Simulator s;
    string x;
    while(x!="OUT ALL")
    {
        getline(cin,x);
        s.Load(x);
    }
    
    return 0;
}
