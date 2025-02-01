#pragma once
#include <concepts>
#include <vector>

template<typename T>
concept AllowedType = std::is_integral_v<T> && sizeof(T) <= 8 || std::is_floating_point_v<T>;

template<AllowedType T>
class Matrix
{
public:
    explicit Matrix(int rows, int cols);

    virtual ~Matrix() = default;

    T& at(size_t row, size_t col);
    const T& at(size_t row, size_t col) const;
    const std::vector<T>& operator[](size_t row);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    [[nodiscard]] inline size_t rows() const noexcept {return m_rows;}
    [[nodiscard]] inline size_t cols() const noexcept {return m_cols;}

protected:
    size_t m_rows = 0;
    size_t m_cols = 0;
    std::vector<std::vector<T>> m_data;
};

template<AllowedType T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

#include "Matrix.tpp"