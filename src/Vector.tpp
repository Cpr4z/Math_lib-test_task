#include "Exceptions.hpp"

template<AllowedType T>
T& Vector<T>::at(size_t pos)
{
    if ((isColumn() && pos >= this->rows()) || (!isColumn() && pos >= this->cols()))
    {
        throw SizeException("index is out of range");
    }

    if (isColumn())
    {
        return this->m_data[pos][0];
    }
    else
    {
        return this->m_data[0][pos];
    }
}

template<AllowedType T>
const T& Vector<T>::at(size_t pos) const
{
    if ((isColumn() && pos >= this->rows()) || (!isColumn() && pos >= this->cols()))
    {
        throw SizeException("index is out of range");
    }

    if (isColumn())
    {
        return this->m_data[pos][0];
    }
    else
    {
        return this->m_data[0][pos];
    }
}

template<AllowedType T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const
{
    if ((this->isColumn() != other.isColumn()) ||
    (this->rows() != other.rows() || this->cols() != other.cols()))
    {
        throw IncompatibleSizeException("you can't summarize vectors with different size");
    }

    Vector<T> result(isColumn() ? this->rows() : this->cols(), isColumn());

    if (this->isColumn())
    {
        for (size_t row = 0; row < this->rows(); ++row)
        {
            result.at(row) = this->at(row) + other.at(row);
        }
    }
    else
    {
        for (size_t col = 0; col < this->cols(); ++col)
        {
            result.at(col) = this->at(col) + other.at(col);
        }
    }
    return result;
}

template<AllowedType T>
Matrix<T> operator*(const Matrix<T>& matrix, const Vector<T>& vector)
{
    bool isColumnVector = vector.isColumn();

    bool isValid = isColumnVector ? (matrix.cols() == vector.rows()) : (matrix.rows() == vector.cols());
    if (!isValid)
    {
        throw IncompatibleSizeException("you entered incorrect size in some dimension of matrix or vector");
    }

    size_t resultRows = isColumnVector ? matrix.rows() : 1;
    size_t resultCols = isColumnVector ? 1 : matrix.cols();

    Matrix<T> result(resultRows, resultCols);

    if (isColumnVector) {
        for (size_t row = 0; row < matrix.rows(); ++row)
        {
            T sum = 0;
            for (size_t col = 0; col < matrix.cols(); ++col)
            {
                sum += matrix.at(row, col) * vector.at(col);
            }
            result.at(row, 0) = sum;
        }
    }
    else
    {
        for (size_t col = 0; col < matrix.cols(); ++col)
        {
            T sum = 0;
            for (size_t row = 0; row < matrix.rows(); ++row)
            {
                sum += vector.at(row) * matrix.at(row, col);
            }
            result.at(0, col) = sum;
        }
    }
    return result;
}

template<AllowedType T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.size(); ++i)
    {
        if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t>)
        {
            os << static_cast<int>(vector.at(i));
        }
        else
        {
            os << vector.at(i);
        }

        if (vector.isColumn())
        {
            os << '\n';
        }
        else
        {
            os << ' ';
        }
    }
    os << std::endl;
    return os;
}



