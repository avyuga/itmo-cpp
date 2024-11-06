#ifndef GRAPH_NODE
#define GRAPH_NODE

static const int MAX_NEIGHBOURS = 10;


class GraphNode{
    private:
        int id;
    
    public:
        int value;
        int num_neighbours;
        int* neighbours_ids;   

        GraphNode(int value, int num_neighbours, int* neighbours_ids);
        GraphNode(const GraphNode& node);
        GraphNode(GraphNode&& moved);
        ~GraphNode();

        GraphNode& operator=(const GraphNode& node);
        GraphNode& operator=(GraphNode&& moved);

        void print();
        void add2value(int v);
};

#endif