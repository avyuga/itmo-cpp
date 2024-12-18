#ifndef SPARSE_VECTOR_H
#define SPARSE_VECTOR_H

#include <sparse_matrix.hpp>

using namespace std;

template <typename T> class SparseVector: public SparseMatrix<T>{
    public:
        SparseVector(vector<T> const& vec, const int& h, const int& w) : SparseMatrix<T>({vec}, h, w){};
        SparseVector(vector<T> const& vec) : SparseMatrix<T>({vec}, vec.size(), 1){};
        SparseVector() : SparseMatrix<T>(){};

        ~SparseVector(){
            this->data.clear();
        };

        SparseVector<T>& transpose() override{
            SparseVector<T>& s = *new SparseVector<T>() ;
            s.data = this->data;
            s.height = this->width; s.width = this->height;
            return s;
        };
};

template <typename T>SparseMatrix<T>& dot(SparseVector<T>& vec1, SparseVector<T>& vec2) {
    SparseMatrix<T>& mat1 = vec1;
    SparseMatrix<T>& mat2 = vec2;
    return dot(mat1, mat2);
}


#endif