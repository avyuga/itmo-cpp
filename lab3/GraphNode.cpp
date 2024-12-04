#include "GraphNode.hpp"

using namespace std;


static int COUNTER = 0;

// конструктор по значению
GraphNode::GraphNode(int val, int num, vector<int> ids){
    id = ++COUNTER;
    value = val;
    num_neighbours = num;
    neighbours_ids = ids;
    // cout << format("Used basic constructor: id={}", id) << endl;
};


// конструктор копирования
GraphNode::GraphNode(const GraphNode& node){
    id = node.id;
    value = node.value;

    num_neighbours = node.num_neighbours;
    neighbours_ids = vector<int>(num_neighbours);

    copy(node.neighbours_ids.begin(), node.neighbours_ids.end(), neighbours_ids.begin());
    // cout << format("Used copy constructor: {} to {}", node.id, id) << endl;
}


// конструктор перемещения
GraphNode::GraphNode(GraphNode&& moved){
    id = moved.id;
    value = moved.value;

    num_neighbours = moved.num_neighbours;
    neighbours_ids = moved.neighbours_ids;
    moved.neighbours_ids.clear();

    // cout << format("Used move constructor: {} to {}", moved.id, id) << endl;
}


// деструктор
GraphNode::~GraphNode(){
    neighbours_ids.clear();
    // cout << format("Deleted GraphNode with id={}", id) << endl;

}


// функция вывода
void GraphNode::print(){
    cout << format("GraphNode with id={}, value={}, num_neighbours={}: ", id, value, num_neighbours);
    copy(neighbours_ids.begin(), neighbours_ids.end(), ostream_iterator<int>(cout, " ")); 
    cout << endl;
}


GraphNode& GraphNode::operator=(const GraphNode& node){
    if (&node != this){
        id = node.id;
        value = node.value;

        num_neighbours = node.num_neighbours;
        neighbours_ids = vector<int>(num_neighbours);
        copy(node.neighbours_ids.begin(), node.neighbours_ids.end(), neighbours_ids.begin());
    }

    // cout << format("Copy Assign id={} to id={}", node.id, id) << endl;
    return *this;
}


GraphNode& GraphNode::operator=(GraphNode&& node){
    if (&node != this){
        id = node.id;
        value = node.value;

        num_neighbours = node.num_neighbours;
        neighbours_ids = node.neighbours_ids;
        node.neighbours_ids.clear();
    }

    // cout << format("Move Assign id={} to id={}", node.id, id) << endl;
    return *this;
}

bool GraphNode::cmp_decrease(const GraphNode& a, const GraphNode& b){
    return a.value < b.value;
}

bool GraphNode::cmp_increase(const GraphNode& a, const GraphNode& b){
    return a.value > b.value;
}

int GraphNode::add(const int& a, const GraphNode& b){
    return a + b.value;
}