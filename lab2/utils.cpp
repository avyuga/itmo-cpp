#include "iostream"
#include <list>
#include <vector>

#include "GraphNode.hpp"
#include "utils.hpp"

using namespace std;


// работа с стандартным вектором в стиле C
GraphNode* update_list(GraphNode *list, int length, int value){
    for (int i=0; i<length; i++){
        list[i].add2value(value);
    }
    return list;
}

// передача и возврат экземпляра в функцию
GraphNode update_neighbour_ids(GraphNode node, int neighbour_id){
    
    int num_neighbours_upd = node.num_neighbours + 1;
    int ids_upd[num_neighbours_upd];
    for (int i=0;i<node.num_neighbours; i++){
        ids_upd[i] = node.neighbours_ids[i];
    }
    ids_upd[node.num_neighbours] = neighbour_id;

    return GraphNode(node.value, num_neighbours_upd, ids_upd);
}

// очистка экземпляра от "соседей". Происходит изменение объекта по ссылке.
void clear_neighbours(GraphNode* node){
    node->num_neighbours = 0;
    node->neighbours_ids = nullptr;
}


// конвертирование c-style массива в список
list<GraphNode> convert2list(int len_list, GraphNode* cstyle_node_list){
    list<GraphNode> node_list;
    for (int j=0; j<len_list; j++){
        node_list.push_back(cstyle_node_list[j]);
    }
    cout << "Created list<GraphNode> with size " << node_list.size() << endl;
    return node_list;
}

// конвертирование c-style массива в вектор
vector<GraphNode> convert2vector(int len_list, GraphNode* cstyle_node_list){
    vector<GraphNode> node_vector;
    for (int j=0; j<len_list; j++){
        node_vector.push_back(cstyle_node_list[j]);
        cout << "... pushed back " << j;
        cout << ", vector capacity now " << node_vector.capacity() << endl;
    }
    cout << "Created vector<GraphNode> with size " << node_vector.size() << endl;
    return node_vector;
}
