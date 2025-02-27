//
// Created by Sergei on 11/29/24.
//

#include "matrix.h"

Matrix::Matrix(const Matrix &rhs) {
    this->rows_count_ = rhs.rows_count_;
    this->columns_count_ = rhs.columns_count_;

    matrix = new int32_t *[rhs.rows_count_];
    for (size_t i = 0; i < rhs.rows_count_; i++) {
        matrix[i] = new int32_t[rhs.columns_count_];
    }

    for (size_t i = 0; i < rhs.rows_count_; i++) {
        for (size_t j = 0; j < rhs.columns_count_; j++) {
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
}

Matrix::Matrix(const size_t &rows_count_, const size_t &columns_count_) {
    this->rows_count_ = rows_count_;
    this->columns_count_ = columns_count_;

    matrix = new int32_t *[rows_count_];
    for (size_t i = 0; i < rows_count_; i++) {
        matrix[i] = new int32_t[columns_count_]();
    }

}

Matrix::~Matrix() {
    for (size_t i = 0; i < rows_count_; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    if (this == &rhs) {
        return *this;
    }

    for (size_t i = 0; i < rows_count_; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    rows_count_ = rhs.rows_count_;
    columns_count_ = rhs.columns_count_;

    matrix = new int32_t *[rows_count_];
    for (size_t i = 0; i < rows_count_; ++i) {
        matrix[i] = new int32_t[columns_count_];
        for (size_t j = 0; j < columns_count_; ++j) {
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
    return *this;
}

size_t Matrix::getColumns() const {
    return columns_count_;
}

size_t Matrix::getRows() const {
    return rows_count_;
}

bool Matrix::operator==(const Matrix &rhs) const {
    if (rows_count_ != rhs.rows_count_ || columns_count_ != rhs.columns_count_) {
        return false;
    }

    for (size_t i = 0; i < rows_count_; i++) {
        for (size_t j = 0; j < columns_count_; j++) {
            if (matrix[i][j] != rhs.matrix[i][j]) return false;
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix &rhs) const {
    return !(matrix == rhs.matrix);
}

Matrix Matrix::operator*=(const size_t num) const {
    for (size_t i = 0; i < rows_count_; i++) {
        for (size_t j = 0; j < columns_count_; j++) {
            matrix[i][j] *= num;
        }
    }

    return *this;
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    Matrix new_matrix(rows_count_, columns_count_);
    if (rows_count_ != rhs.rows_count_ || columns_count_ != rhs.columns_count_)
        throw std::out_of_range("Different matrix sizes.");
    else
        for (size_t i = 0; i < rows_count_; i++) {
            for (size_t j = 0; j < columns_count_; j++) {
                new_matrix.matrix[i][j] = rhs.matrix[i][j] + matrix[i][j];
            }
        }
    return new_matrix;
}

Matrix::ProxyRow Matrix::operator[](const size_t &index) const {
    if( rows_count_ != 0 && index >= rows_count_){
        throw std::out_of_range("Row index " + std::to_string(index) + " out of range [0.." + std::to_string(rows_count_ - 1) + "]");
    }
    else {
        return ProxyRow(matrix[index], columns_count_);
    }
}

int32_t &Matrix::ProxyRow::operator[](const size_t &index) const {
    if( columns_count_ != 0 && index >= columns_count_ )
        throw std::out_of_range("Column index " + std::to_string(index) + " out of range [0.." + std::to_string(columns_count_ - 1) + "]");
    return row_[index];
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (size_t i = 0; i < matrix.getRows(); ++i) {
        for (size_t j = 0; j < matrix.getColumns(); ++j) {
            os << matrix.matrix[i][j];
            if (j < matrix.getColumns() - 1) {
                os << "\t";
            }
        }
        os << '\n';
    }

    return os;
}