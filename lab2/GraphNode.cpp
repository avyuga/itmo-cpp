#include <iostream>
#include "string"
#include <format>

#include "GraphNode.hpp"

using namespace std;


static int COUNTER = 0;


// конструктор по значению
GraphNode::GraphNode(int val, int num, int* ids){
    id = ++COUNTER;
    value = val;
    num_neighbours = num;

    neighbours_ids = new int[num_neighbours];
    for (int j=0; j<num_neighbours; j++){
        neighbours_ids[j] = ids[j];
    } 
    cout << format("Used basic constructor: id={}", id) << endl;
};


// конструктор копирования
GraphNode::GraphNode(const GraphNode& node){
    id = ++COUNTER;
    value = node.value;

    num_neighbours = node.num_neighbours;
    neighbours_ids = new int[num_neighbours];
    for (int j=0; j<num_neighbours; j++){
        neighbours_ids[j] = node.neighbours_ids[j];
    } 

    cout << format("Used copy constructor: {} to {}", node.id, id) << endl;
}


// конструктор перемещения
GraphNode::GraphNode(GraphNode&& moved){
    id = ++COUNTER;
    value = moved.value;

    num_neighbours = moved.num_neighbours;
    neighbours_ids = moved.neighbours_ids;
    moved.neighbours_ids = nullptr;

    cout << format("Used move constructor: {} to {}", moved.id, id) << endl;
}


// деструктор
GraphNode::~GraphNode(){
    delete neighbours_ids;
    cout << format("Deleted GraphNode with id={}", id) << endl;

}


// функция вывода
void GraphNode::print(){
    cout << format("GraphNode with id={}, value={}, num_neighbours={}: ", id, value, num_neighbours);
    for (int j=0; j<num_neighbours; j++){
        cout << neighbours_ids[j] << " ";
    } 
    cout << endl;
}


// функция обновления
void GraphNode::add2value(int v){
    value += v;
}


GraphNode& GraphNode::operator=(const GraphNode& node){
    if (&node != this){
        id = ++COUNTER;
        value = node.value;

        num_neighbours = node.num_neighbours;
        neighbours_ids = new int[num_neighbours];
        for (int j=0; j<num_neighbours; j++){
            neighbours_ids[j] = node.neighbours_ids[j];
        } 
    }

    cout << format("Copy Assign id={} to id={}", node.id, id) << endl;
    return *this;
}


GraphNode& GraphNode::operator=(GraphNode&& node){
    if (&node != this){
        id = ++COUNTER;
        value = node.value;

        num_neighbours = node.num_neighbours;
        neighbours_ids = node.neighbours_ids;
        node.neighbours_ids = nullptr;
    }

    cout << format("Move Assign id={} to id={}", node.id, id) << endl;
    return *this;
}