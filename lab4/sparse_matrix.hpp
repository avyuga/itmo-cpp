#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>
#include <format>
#include <iterator>
#include <vector>
#include <ranges>
#include <map>
#include <assert.h>
#include <numeric>
#include <cmath>


using namespace std;


template <typename T> class SparseMatrix{
    private:
        void vec2sparse(vector<vector<T>> const& vec){
            size_t full_size = 0;
            for (vector<T> v: vec) full_size += v.size();

            vector<T> concat_vec;
            concat_vec.reserve(full_size);
            for(vector<T> v : vec) concat_vec.insert(concat_vec.end(), v.begin(), v.end());

            auto range = views::iota((unsigned long long)0, full_size);
            auto binary_op = [](const int& a, const T& b){return make_pair(a, b);};

            vector<pair<int, T>> pairs_vec;
            pairs_vec.reserve(full_size);
            transform(range.begin(), range.end(), concat_vec.begin(), back_inserter(pairs_vec), binary_op);

            auto iter = remove_if(pairs_vec.begin(), pairs_vec.end(), [](IdxVal x){return x.second == 0;});
            pairs_vec.erase(iter, pairs_vec.end());

            this->data = map(pairs_vec.begin(), pairs_vec.end());

            concat_vec.clear();
            pairs_vec.clear();
        };


    public:
        typedef pair<int,T> IdxVal;
        map<int, T> data {};
        int height {0};
        int width {0};

        SparseMatrix(vector<vector<T>> const& vec, const int& h, const int& w){
            this->height = h; this->width = w;
            this->vec2sparse(vec);
        };
        SparseMatrix(map<int, T> const& data, const int& h, const int& w){
            this->height = h; this->width = w;
            this->data = data;
        };
        SparseMatrix(){};

        ~SparseMatrix(){
            this->data.clear();
        };

        void print(){
            for (auto& p: this->data){
                    cout << format("{}: {}, ", p.first, p.second);
                }
            cout << format("Size: {}x{}", this->height, this->width) << endl;
        };

        virtual SparseMatrix<T>& transpose(){
            SparseMatrix<T>& s = *new SparseMatrix<T>();
            vector<int> converted_idxs;
            converted_idxs.reserve(this->data.size());

            transform(this->data.begin(), this->data.end(), back_inserter(converted_idxs), 
                      [this](const pair<int, T>& p){return p.first / this->width + (p.first % this->width)*this->height;}
                      );
                      
            auto binary_op = [](int& a, pair<int, T> b){return make_pair(a, b.second);};
            transform(converted_idxs.begin(), converted_idxs.end(), this->data.begin(), inserter(s.data, s.data.end()), binary_op);

            s.height = this->width; s.width = this->height;
            return s;
        };

        virtual SparseMatrix<T>& operator+(SparseMatrix<T>& sm){
            map<int, T> data = this->data;
            data = accumulate(sm.data.begin(), sm.data.end(), data, 
                [](map<int, T> m, const pair<int, T>&p){
                    return (m[p.first]+= p.second, m);
                }
            );
            erase_if(data, [](const auto& p){return p.second == 0;});

            return *new SparseMatrix<T>(data, this->height, this->width);
        };

        virtual SparseMatrix<T>& operator*(T val){
            map<int, T> data;  
            transform(this->data.begin(), this->data.end(), inserter(data, data.end()),
                [val](pair<const int, T>& c){return make_pair(c.first, c.second * val);}
            );
            erase_if(data, [](const auto& p){return p.second == 0;});

            return *new SparseMatrix<T>(data, this->height, this->width);
        };

        virtual SparseMatrix<T>& operator^(int val){
            map<int, T> data;  
            transform(this->data.begin(), this->data.end(), inserter(data, data.end()),
                [val](pair<const int, T>& c){return make_pair(c.first, pow(c.second, val));}
            );
            erase_if(data, [](const auto& p){return p.second == 0;});

            return *new SparseMatrix<T>(data, this->height, this->width);
        };
          
};


template<typename T> SparseMatrix<T>& dot(SparseMatrix<T>& a, SparseMatrix<T>& b) {
    assert(a.width == b.height);
    SparseMatrix<T>& result = *new SparseMatrix<T>();
    result.height = a.height;
    result.width = b.width;
    
    // Create column-wise index for matrix b to speed up lookups
    map<int, map<int, T>> b_cols;
    for (const auto& b_elem : b.data) {
        int row = b_elem.first / b.width;
        int col = b_elem.first % b.width;
        b_cols[row][col] = b_elem.second;
    }
    
    // Perform multiplication with optimized lookups
    for (const auto& a_elem : a.data) {
        int i = a_elem.first / a.width;  // Row in a
        int k = a_elem.first % a.width;  // Col in a
        
        auto it = b_cols.find(k);
        if (it != b_cols.end()) {
            for (const auto& [j, b_val] : it->second) {
                int result_idx = i * b.width + j;
                result.data[result_idx] += a_elem.second * b_val;
            }
        }
    }
    
    erase_if(result.data, [](const auto& p){return p.second == 0;}); 
    return result;
}



template<typename T> SparseMatrix<T>& matrix_power(SparseMatrix<T>& sm, int val){
    assert (sm.width == sm.height);
    assert (val > 0);

    if (val == 1) return sm;
    
    SparseMatrix<T>& temp = sm;
    for (int i = 1; i < val; i++){
        temp = dot(temp, sm);
    }    
    return temp;
};

template<typename T> SparseMatrix<T>& matrix_exp(SparseMatrix<T>& A, int terms = 10) {
    assert(A.width == A.height);
    
    SparseMatrix<T>& result = *new SparseMatrix<T>();
    result.height = A.height;
    result.width = A.width;
    for(int i = 0; i < A.height; i++) {
        result.data[i * A.width + i] = 1;
    }
    
    SparseMatrix<T>& term = *new SparseMatrix<T>();
    term.height = A.height;
    term.width = A.width;
    for(int i = 0; i < A.height; i++) {
        term.data[i * A.width + i] = 1;
    }
    
    T factorial = 1;
    for(int i = 1; i <= terms; i++) {
        term = dot(term, A);
        factorial *= i;
        auto scaled_term = term * (1.0/factorial);
        result = result + scaled_term;
    }
    
    return result;
}

template<typename T> SparseMatrix<T>& matrix_log(SparseMatrix<T>& A, int terms = 10) {
    assert(A.width == A.height);
    
    SparseMatrix<T>& result = *new SparseMatrix<T>();
    result.height = A.height;
    result.width = A.width;
    
    SparseMatrix<T>& X = *new SparseMatrix<T>();
    X.height = A.height;
    X.width = A.width;
    X = A;
    for(int i = 0; i < A.height; i++) {
        int idx = i * A.width + i;
        X.data[idx] = (X.data.count(idx) ? X.data[idx] : 0) - 1;
    }
    
    // Calculate log series: ln(I + X) = X - X²/2 + X³/3 - X⁴/4 + ...
    SparseMatrix<T>& term = X;
    result = X;
    
    for(int i = 2; i <= terms; i++) {
        term = dot(term, X);
        auto scaled_term = term * (((i % 2 == 0) ? -1.0 : 1.0) / i);
        result = result + scaled_term;
    }
    
    return result;
}

template<typename T> SparseMatrix<T>& matrix_power_real(SparseMatrix<T>& A, double power, int terms = 10) {
    assert(A.width == A.height);
    
    auto log_A = matrix_log(A, terms);
    auto scaled_log = log_A * power;
    return matrix_exp(scaled_log, terms);
}


#endif