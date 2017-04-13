#include <iostream>
#include <vector>
#include "nDArray/nDArray.hpp"
#include <chrono>
#include <ctime>
using namespace std;

#define now std::chrono::system_clock::now
using time_point=std::chrono::time_point<std::chrono::system_clock>;
#define micro_sec std::chrono::duration_cast<std::chrono::microseconds>

template<class T>
using Array2D=vector<vector<T>>;
template<class T>
using Array1D=vector<T>;
template<class T>
void set_mat(T& elem, int & cnt) {
    elem = cnt++;
}

//template<class T>
//void set_mat(nDArray<T,1> & mat, int & cnt) {
//}

template<class T, int dim>
void set_mat(nDArray<T, dim> & mat, int & cnt) {
    for(int i= 0; i < mat.size(); ++i) {
        set_mat<T>(mat[i], cnt);
    }
}

void create_time_cmp(int len) {
    time_point start, end;
    start = now();
    nDArray<int, 2> _4D_mat(len, len);
    end = now();
    int new_arr_time = micro_sec(end-start).count();
    cout << "user array creation time=" << new_arr_time << "ms" << endl;

    start = now();
    Array2D<int> vec2D(len, Array1D<int>(len));
    end = now();
    int old_arr_time = micro_sec(end-start).count();
    cout << "vector array creation time=" << old_arr_time << " ms" << endl;
}

int main(int argc, char ** argv) {
    const int len = 1000;
    nDArray<int, 2> _4D_mat(len, len);
    int cnt = 0;
    set_mat(_4D_mat, cnt);
    Array2D<int> vec2D(len, Array1D<int>(len));

    create_time_cmp(len);
    //for(int i = 0; i < 2; ++i) {
        //for(int j = 0; j < 2; ++j) {
            //cout << _4D_mat[i][j] << ' ';
        //}
        //cout << endl;
    //}
    
}
