#include "sparse_matrix.hpp"
#include "sparse_vector.hpp"
#include "timer.h"

#include <Eigen/Dense>
#include <Eigen/SparseCore>


using namespace std;    


Eigen::MatrixXi& convert_to_eigen(vector<vector<int>> m){
    Eigen::MatrixXi& m1_eigen = *new Eigen::MatrixXi(m.size(), m[0].size());
    for(size_t i = 0; i < m.size(); ++i) {
        for(size_t j = 0; j < m[i].size(); ++j) {
            m1_eigen(i, j) = m[i][j];
        }
    }
    return m1_eigen;
}

int main(){

    Timer timer;

    cout << "Matrixes to SparseMatrix" << endl;
    vector<vector<int>> m1 = {
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, 
        {2, 0, 12, 0, 0, 0, 0, 0, -1, 0}, 
        {0, 3, 0, 14, 0, 0, 0, 2, 0, 0}, 
        {5, 9, 0, 0, 0, 3, 0, 0, 0, 7},
        {0, 1, 0, 16, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, -1, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

    };

    Eigen::MatrixXi m1_eigen = convert_to_eigen(m1);
    Eigen::SparseMatrix<int> m1_sparse = m1_eigen.sparseView();

    SparseMatrix sm = SparseMatrix<int>(m1, 10, 10);
    sm.print();
    auto smT = sm.transpose();
    
    vector<vector<int>> m2 = {
        {0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, 
        {-2, 0, 4, 0, 0, 0, 0, 0, -1, 0}, 
        {0, 3, 0, -14, 0, 0, 0, 2, 0, 0}, 
        {-5, -9, 0, -10, 0, 3, 0, 0, 0, 7},
        {0, -1, 0, -20, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, -1, 0, 0},
        {0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0}

    };
    Eigen::MatrixXi m2_eigen = convert_to_eigen(m2);
    Eigen::SparseMatrix<int> m2_sparse = m2_eigen.sparseView(); 

    SparseMatrix sm2 = SparseMatrix<int>(m2, 10, 10);

    cout << "Operations of multiplication and summarization" << endl;
    auto summ = sm * 3 + sm2*(-1);
    summ.print();
    cout << endl;


    cout << "Vector to SparseVector: ";
    vector<int> v = {1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
                    0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    SparseVector sv = SparseVector<int>(v);
    sv.print();

    Eigen::Map<Eigen::VectorXi> sv_dense(v.data(), v.size());
    Eigen::SparseVector<int> sv_eigen = sv_dense.sparseView();
    cout << "SV using Eigen: " << sv_eigen << endl;


    auto svT = sv.transpose();

    cout << "Multiply SparseVector by 4: " << endl;
    auto sum2 = sv * 4;
    sum2.print();
    cout << endl;

    cout << "Raise SparseVector to the power of 2: " << endl;
    auto pow2 = sv ^ 2;
    pow2.print();
    cout << endl;


    cout << "Dot product of SparseVector and SparseVector.T: " << endl;
    cout << " * Using Custom SparseVector took ";
    timer.tic();
    auto dot_sv = dot(sv, svT);
    cout << timer.toc() << " mcs" << endl;

    cout << " * Using Eigen Dense Vector took ";
    timer.tic();
    auto dot_sv_dense = sv_dense*sv_dense.transpose();
    cout << timer.toc() << " mcs" << endl;

    cout << " * Using Eigen Sparse Vector took ";
    timer.tic();
    auto dot_sv_sparse = sv_eigen*sv_eigen.transpose();
    cout << timer.toc() << " mcs" << endl;
    cout << endl;


    cout << "Dot product of matrixes" << endl;  
    cout << " * Using Custom SparseMatrix took ";  
    timer.tic();
    auto res = dot(sm, smT);
    auto diff = timer.toc();
    cout << diff << " mcs" << endl;

    cout << " * Using Eigen Dense Matrix took ";  
    timer.tic();
    auto res3 = m1_eigen * m2_eigen.transpose();
    diff = timer.toc();
    cout << diff << " mcs" << endl;

    cout << " * Using Eigen Sparse Matrix took ";  
    timer.tic();
    auto res2 = m1_sparse * m2_sparse.transpose();
    diff = timer.toc();
    cout << diff << " mcs" << endl;


    cout << "\nFinished successfully!" << endl;
    return 0;
}