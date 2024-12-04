#ifndef GRAPH_NODE
#define GRAPH_NODE

#include <iostream>
#include <format>
#include <iterator>
#include <vector>
#include "string"


class GraphNode{
    private:
        int id;
    
    public:
        int value;
        int num_neighbours;
        std::vector<int> neighbours_ids;   

        GraphNode(int value, int num_neighbours, std::vector<int> neighbours_ids);
        GraphNode(const GraphNode& node);
        GraphNode(GraphNode&& moved);
        ~GraphNode();

        GraphNode& operator=(const GraphNode& node);
        GraphNode& operator=(GraphNode&& moved);

        void print();

        static bool cmp_decrease(const GraphNode& a, const GraphNode& b);
        static bool cmp_increase(const GraphNode& a, const GraphNode& b);

        static int add(const int& a, const GraphNode& b); 

};



#endif