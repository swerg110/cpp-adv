//
// Created by Sergei on 11/29/24.
//
#pragma once

#include <iostream>

class Matrix {
public:
    class ProxyRow {
    public:
        ProxyRow(int32_t *pRow, int32_t columns_count) : row_(pRow),  columns_count_(columns_count){};
        ~ProxyRow() {};

        int32_t &operator[](const size_t &index) const;

    private:
        int32_t *row_;
        int32_t columns_count_;
    };

    Matrix(const size_t &d1, const size_t &d2);

    Matrix(const Matrix &rhs);

    ~Matrix();

    Matrix &operator=(const Matrix &rhs);

    Matrix operator+(const Matrix &rhs) const;

    Matrix operator*=(const size_t num) const;

    bool operator==(const Matrix &rhs) const;

    bool operator!=(const Matrix &rhs) const;

    size_t getRows() const;

    size_t getColumns() const;

    ProxyRow operator[](const size_t &index) const;

    friend std::ostream &operator<<(std::ostream &, const Matrix &);

private:
    int32_t **matrix;
    size_t	rows_count_;
    size_t	columns_count_;

};


