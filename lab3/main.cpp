#include "GraphNode.hpp"

#include <iostream>
#include <iterator>

#include <list>
#include <vector>
#include <algorithm>
#include <numeric>

#include <format>
#include <utility>
#include <random>


using namespace std;


int getRandomValue(){
    static random_device dev;
    static mt19937 rng(dev());
    static uniform_int_distribution<int> uint_dist10(-100, 1000);

    return uint_dist10(rng);
}

int getRandomLen(){
    static random_device dev;
    static mt19937 rng(dev());
    static uniform_int_distribution<int> uint_dist10(1, 5);

    return uint_dist10(rng);
}

int getRandomNeighbour(){
    static random_device dev;
    static mt19937 rng(dev());
    static uniform_int_distribution<int> uint_dist10(1, 600);

    return uint_dist10(rng);
}


int main(){

    
    int N = 10; // Number of values in the list
    cout << "1. Creating vector V1 with " << N << " elements" << endl;
    vector<GraphNode> v1;
    v1.reserve(N);

    for (int i=0; i<N; i++){
        int value = getRandomValue();
        int randomLen = getRandomLen();
        vector<int> randomNeighbours(randomLen);
        generate(randomNeighbours.begin(), randomNeighbours.end(), getRandomNeighbour);

        GraphNode node = GraphNode(value, randomLen, randomNeighbours);
        v1.push_back(node);
    }

    for (auto iter = v1.begin(); iter != v1.end(); iter++) iter -> print();
    cout << endl;
    


    int start_idx = 4;
    int end_idx = 13;
    if (end_idx > N) end_idx = N;

    cout << "2. Creating vector V2 with elements from v1(" << start_idx << ", " << end_idx << ")" << endl;
    vector<GraphNode> v2;
    v2.reserve(end_idx-start_idx);
    v2.assign(v1.begin()+start_idx, v1.begin()+end_idx);
    for (auto iter = v2.begin(); iter != v2.end(); iter++) iter -> print();
    cout << endl;



    int topN = 3;
    cout << "3. Sort V1 and create a list L1 with " << topN << " top elements from V1" << endl;
    sort(v1.begin(), v1.end(), GraphNode::cmp_increase);
    list<GraphNode> l1(v1.begin(), v1.begin()+topN);

    for (auto iter = l1.begin(); iter != l1.end(); iter++) iter -> print();
    cout << endl;



    int leastN = 4;
    cout << "4. Sort V2 and create a list L2 with " << leastN << " least elements from V2" << endl;
    sort(v2.begin(), v2.end(), GraphNode::cmp_decrease);
    list<GraphNode> l2(v2.begin(), v2.begin()+leastN);

    for (auto iter = l2.begin(); iter != l2.end(); iter++) iter -> print();
    cout << endl;



    cout << "5. Remove transferred elements from V1 and V2" << endl;
    cout << "V1: size before " << v1.size();
    v1.erase(v1.begin(), v1.begin()+topN);
    cout << ", size after " << v1.size() << endl;

    cout << "V2: size before " << v2.size();
    v2.erase(v2.begin(), v2.begin()+leastN);
    cout << ", size after " << v2.size() << endl;
    cout << endl;
    
    

    cout << "6. Find mean value & regroup L1" << endl;
    int sum = accumulate(l1.begin(), l1.end(), 0, GraphNode::add);
    float mean_val = static_cast<float>(sum) / l1.size();
    auto iter = find_if(l1.begin(), l1.end(), [mean_val](GraphNode x){return x.value < mean_val;});
    rotate(l1.begin(), iter, l1.end());
    for (auto iter = l1.begin(); iter != l1.end(); iter++) iter -> print();
    cout << endl;



    cout << "7. Remove all elements from L2 which are odd" << endl;
    iter = remove_if(l2.begin(), l2.end(), [](GraphNode x){return x.value % 2 != 0;});
    l2.erase(iter, l2.end());
    for (auto iter = l2.begin(); iter != l2.end(); iter++) iter -> print();
    cout << endl;



    cout << "8. Create vector V3 from elements present in both V1 and V2" << endl;
    sort(v1.begin(), v1.end(), GraphNode::cmp_decrease);
    sort(v2.begin(), v2.end(), GraphNode::cmp_decrease);

    vector<GraphNode> v3;
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3), GraphNode::cmp_decrease);

    for (auto iter = v3.begin(); iter != v3.end(); iter++) iter -> print();
    cout << endl;



    cout << "9. L1, L2 to Pairs" << endl;
    typedef pair<GraphNode,GraphNode> NodePair;

    list<NodePair> pairs_from_lists;

    int lengthL1 = l1.size();
    int lengthL2 = l2.size();

    if (lengthL1 > lengthL2) {
        auto begin = l1.begin();
        auto end = l1.begin();
        advance(end, lengthL1-lengthL2);
        l1.erase(begin, end);
    } else if (lengthL1 < lengthL2){
        auto begin = l2.begin();
        auto end = l2.begin();
        advance(end, lengthL2-lengthL1);
        l2.erase(begin, end);
    }
    auto binary_op = [](const GraphNode& a, const GraphNode& b){return make_pair(a, b);};
    transform(l2.begin(), l2.end(), l1.begin(), back_inserter(pairs_from_lists), binary_op);

    for (auto p: pairs_from_lists){
        cout << format("GraphNode with value={} & GraphNode with value={}", p.first.value, p.second.value) << endl;
    }
    cout << endl;



    cout << "10. V1, V2 to Pairs" << endl;
    vector<NodePair> pairs_from_vectors;

    if (v1.size() > v2.size()) {
        transform(v2.rbegin(), v2.rend(), v1.rbegin(), back_inserter(pairs_from_vectors), binary_op);
    } else{
        transform(v1.rbegin(), v1.rend(), v2.rbegin(), back_inserter(pairs_from_vectors), binary_op);
    }

    for (auto p: pairs_from_vectors){
        cout << format("GraphNode with value={} & GraphNode with value={}", p.first.value, p.second.value) << endl;
    }
    cout << endl;


    cout << "Finished execution successfully" << endl;
    
    return 0;
}