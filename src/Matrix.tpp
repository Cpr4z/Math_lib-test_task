#include <iostream>
#include "Exceptions.hpp"

template<AllowedType T>
Matrix<T>::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        throw SizeException("you entered size in some dimension zero or less than zero");
    }

    m_rows = rows;
    m_cols = cols;
    m_data = std::vector(m_rows, std::vector<T>(m_cols));
}

template<AllowedType T>
T& Matrix<T>::at(size_t row, size_t col)
{
    if (row >= rows() || col >= cols())
    {
        throw IndexException("you are out of range");
    }
    return m_data[row][col];
}

template<AllowedType T>
const T& Matrix<T>::at(size_t row, size_t col) const
{
    if (row >= rows() || col >= cols())
    {
        throw IndexException("you are out of range");
    }
    return m_data[row][col];
}

template<AllowedType T>
const std::vector<T>& Matrix<T>::operator[](size_t row)
{
    if (row >= rows())
    {
        throw IndexException("you are out of range");
    }
    return m_data[row];
}

template<AllowedType T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    if (rows() != other.rows() || cols() != other.cols())
    {
        throw SizeException("you can't summarize matrices with different size");
    }

    Matrix<T> result(rows(), cols());
    for (size_t row = 0; row < rows(); ++row)
    {
        for (size_t col = 0; col < cols(); ++col)
        {
            result.at(row, col) = at(row, col) + other.at(row, col);
        }
    }

    return result;
}

template<AllowedType T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
    if (rows() != other.rows())
    {
        throw SizeException("you can't multiply matrices with different size");
    }

    Matrix<T> result(rows(), other.cols());
    for (size_t i = 0; i < rows(); ++i)
    {
        for (size_t j = 0; j < other.cols(); ++j)
        {
            T sum = 0;
            for (size_t k = 0; k < cols(); ++k)
            {
                sum += at(i, k) * other.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

template<AllowedType T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
    for (size_t row = 0; row < matrix.rows(); ++row)
    {
        for (size_t col = 0; col < matrix.cols(); ++col)
        {
            if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t>)
            {
                os << static_cast<int>(matrix.at(row, col));
            }
            else
            {
                os << matrix.at(row, col);
            }
            if (col < matrix.cols() - 1)
            {
                os << " ";
            }
        }
        os << '\n';
    }
    os << std::endl;
    return os;
}