#include "GraphNode.hpp"
#include "utils.hpp"
#include <utility>
#include "iostream"
#include <list>
#include <vector>

using namespace std;


int main(){

    cout << ">>> Testing Different constructors" << endl;

    int value = 5;
    int num_neighbours = 3;
    int neighbors[3] = {10, 11, 12};

    // basic constructor
    GraphNode node = GraphNode(value, num_neighbours, neighbors);
    node.print();

    // copy constructor
    GraphNode node_v2 = GraphNode(node);
    node_v2.print();

    GraphNode node_v3 = GraphNode(move(node_v2));
    node_v3.print();

    cout << endl;

    cout << ">>> Testing Different Assign operations" << endl;
    node_v2 = node;
    node_v2.print(); 

    node_v3 = move(node_v3);
    node_v3.print();
    cout << endl;

    cout << ">>> C-style arrays & operations" << endl;

    int list_length = 7;
    GraphNode graph_list [7] = {
        GraphNode(1, num_neighbours, neighbors),
        GraphNode(2, num_neighbours, neighbors),
        GraphNode(3, num_neighbours, neighbors),
        GraphNode(4, num_neighbours, neighbors),
        GraphNode(5, num_neighbours, neighbors),
        GraphNode(6, num_neighbours, neighbors),
        GraphNode(7, num_neighbours, neighbors)
    };

    int value2add = 4;
    GraphNode* graph_list_v2 = update_list(graph_list, list_length, value2add);
    for (int i=0; i<7; i++){
        graph_list_v2[i].print();
    }
    cout << endl;

    cout << ">>> Created node_v4 from node (added neighbour)" << endl;
    GraphNode node_v4 = update_neighbour_ids(node, 21);
    node_v4.print();
    cout << endl;

    cout << ">>> Cleared node_v4 from all neighbors" << endl;
    clear_neighbours(&node_v4);
    node_v4.print();
    cout << endl;


    cout << ">>> C-Array to List & Using list methods" << endl;
    list<GraphNode> node_list = convert2list(list_length, graph_list);
    cout << endl;

    cout << ">>> Resize vector to size 9" << endl;
    node_list.resize(9, node_v4);
    cout << endl;


    // такой вывод списка вызывает лишнее копирование элементов
    // cout << "Simple list std::cout" << endl;
    // for (GraphNode n : node_list)
    //     n.print();
    // cout << endl;

    // вывод через генератор не делает лишних копирований
    cout << "Generator std::cout" << endl;
    // list<GraphNode>::iterator = auto
    for (auto iter = node_list.begin(); iter != node_list.end(); iter++)
        iter -> print();
    cout << endl;


    cout << ">>> C-Array to Vector & Using vector methods" << endl;
    vector<GraphNode> node_vector = convert2vector(list_length, graph_list);
    node_vector[5].print();
    cout << endl;
  

    cout << endl;

    return 0;
}