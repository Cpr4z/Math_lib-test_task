#pragma once
#include "Matrix.hpp"

template<AllowedType T>
class Vector : public Matrix<T>
{
public:
    explicit Vector(size_t size, bool is_column = true): Matrix<T>(is_column ? size : 1, is_column ? 1 : size),
                                                m_isColumn(is_column){}

    ~Vector() = default;

    T& at(size_t pos);
    const T& at(size_t pos) const;
    Vector operator+(const Vector<T>&) const;
    [[nodiscard]] inline size_t size() const noexcept {return m_isColumn ? this->rows() : this->cols();}
    [[nodiscard]] inline bool isColumn() const noexcept {return m_isColumn;}

private:
    bool m_isColumn;
};

template<AllowedType T>
Matrix<T> operator*(const Matrix<T>& matrix, const Vector<T>& vector);

template<AllowedType T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector);

#include "Vector.tpp"