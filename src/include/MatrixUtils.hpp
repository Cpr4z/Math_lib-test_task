#pragma once
#include "Matrix.hpp"
#include <limits>
#include <random>
#include <thread>

namespace MathUtils
{
    template<AllowedType T>
    void fillEntityRandom(Matrix<T>& matrix)
    {
        std::mt19937 generator(std::random_device{}());

        if constexpr (std::is_integral_v<T>)
        {
            std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
            for (size_t row = 0; row < matrix.rows(); ++row)
            {
                for (size_t col = 0; col < matrix.cols(); ++col)
                {
                    matrix.at(row, col) = dist(generator);
                }
            }
        }
        else if constexpr (std::is_floating_point_v<T>)
        {
            std::uniform_real_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
            for (size_t row = 0; row < matrix.rows(); ++row)
            {
                for (size_t col = 0; col < matrix.cols(); ++col)
                {
                    matrix.at(row, col) = dist(generator);
                }
            }
        }
    }

    template <AllowedType T>
    void multiplyPart(const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& result,
                      size_t startRow, size_t endRow)
    {
        size_t colsA = A.cols();
        size_t colsB = B.cols();

        for (size_t row = startRow; row < endRow; ++row)
        {
            for (size_t col = 0; col < colsB; ++col)
            {
                T sum = 0;
                for (size_t k = 0; k < colsA; ++k)
                {
                    sum += A.at(row, k) * B.at(k, col);
                }
                result.at(row, col) = sum;
            }
        }
    }

    template <AllowedType T>
    Matrix<T> multiplyMatricesParallel(const Matrix<T>& A, const Matrix<T>& B)
    {

        size_t rowsA = A.rows();
        size_t colsB = B.cols();

        Matrix<T> result(rowsA, colsB);

        size_t numThreads = std::min(size_t(std::thread::hardware_concurrency()), rowsA);
        size_t rowsPerThread = rowsA / numThreads;
        size_t remainingRows = rowsA % numThreads;

        std::vector<std::thread> threads;
        size_t startRow = 0;

        for (size_t i = 0; i < numThreads; ++i)
        {
            size_t endRow = startRow + rowsPerThread + (i < remainingRows ? 1 : 0);
            threads.emplace_back(multiplyPart<T>, std::cref(A), std::cref(B), std::ref(result), startRow, endRow);
            startRow = endRow;
        }

        //can't include RAII thread std::jthread
        for (auto& thread: threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
        return result;
    }
}