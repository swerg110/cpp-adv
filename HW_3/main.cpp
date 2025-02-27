//
// Created by Sergei on 12/14/24.
//
#include "matrix.h"
int main(){
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);


    m[1][2] = 5; // строка 1, колонка 2
    double x = m[4][1];

    m *= 3; // умножение на число

    Matrix m1(rows, cols);

    if (m1 == m)
    {
    }
    Matrix m2 = m1 + m;
    std::cout << m2 << std::endl;



    return 0;
}