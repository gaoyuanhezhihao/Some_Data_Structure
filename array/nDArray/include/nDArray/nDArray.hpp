#ifndef NDARRAY_H
#define NDARRAY_H

#include <vector>
template<class T, int Dim>
class nDArray{
    public:
        nDArray()=default;
        template<typename...Args>
            nDArray(Args... all_args)  {
                init(all_args...);
            }
        template<typename...Args>
            void init(const int len, Args... rest_arg){
                pt = new nDArray<T, Dim-1>[len];
                _len = len;
                for(int i = 0; i< len; ++i) {
                    pt[i].init(rest_arg...);
                }
            }

        template<typename...Args>
            T& at(const int idx, Args... rest_arg) {
                return pt[idx].at(rest_arg...);
            }
        nDArray<T,Dim-1> & operator[](const int idx) {
            return pt[idx];
        }
        int size() {
            return _len;
        }
        ~nDArray() {
            delete[] pt;
        }
    private:
        int _len;
        nDArray<T, Dim-1> * pt;
};

template<class T>
class nDArray<T,1>{
    public:
        template<typename...Args>
            void init(const int len) {
                pt = new T[len];
                _len = len;
            }

        T& at(const int idx) {
            return pt[idx];
        }

        int size() {
            return _len;
        }
        ~nDArray() {
            delete[] pt;
        }

        T& operator[](const int idx) {
            return pt[idx];
        }
    private:
        int _len;
        T * pt;
};

#endif //NDARRAY_H
