#pragma once
#include "Vector.h"
#include <vector>
#include <stdexcept>
#include <iostream>


class Matrix {
    std::vector<std::vector<double>> internal_storage;

    void verify_size();

public:

    // Public constructors.
    Matrix(std::initializer_list< std::initializer_list<double>> matrix);
    Matrix(std::vector<std::vector<double>> matrix);
    explicit Matrix(const Vector& V);
    explicit Matrix(const size_t& size);
    explicit Matrix(const size_t& x, const size_t& y);
    
    // Methods.
    size_t get_col_count() const noexcept;
    size_t get_row_count() const noexcept;
    std::vector<std::vector<double>> get_internal_storage() const noexcept;
    Matrix transpose() const;
    void print() const noexcept;
    double trace() const;
    static Matrix identity(const size_t& num) noexcept;

    // Iterators. Templates (auto) in header only.
    auto begin() const {
        return internal_storage.begin();
    }

    auto end() const {
        return internal_storage.end();
    }

    // Operator overloading.
    std::vector<double>& operator[](const size_t& index);
    bool operator==(const Matrix& M) const noexcept;
    bool operator==(const Vector& V) const noexcept;
    Matrix operator-() const noexcept;
    friend Matrix operator*(const Matrix& M, const Vector& V);
    friend Matrix operator*(const Matrix& M0, const Matrix& M1);
    friend Matrix operator*(const Matrix& M, const double& num) noexcept;
    friend Matrix operator*(const double& num, const Matrix& M) noexcept;
    friend Matrix operator/(const Matrix& M, const double& num) noexcept;
    
};
