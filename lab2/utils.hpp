#include <list>
#include <vector>

#include "GraphNode.hpp"


// GraphNode* create_basic_list(int length, int num_neighbours, int* ids);
GraphNode* update_list(GraphNode *list, int length, int value2add);
GraphNode update_neighbour_ids(GraphNode node, int neighbour_id);
void clear_neighbours(GraphNode* node);

std::list<GraphNode> convert2list(int len_list, GraphNode* cstyle_node_list);
std::vector<GraphNode> convert2vector(int len_list, GraphNode* cstyle_node_list);