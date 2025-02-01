#include "Matrix.hpp"
#include "Vector.hpp"
#include "MatrixUtils.hpp"

namespace TestsInfrastructure
{
    using namespace MathUtils;

    template<typename Func, typename ...Args>
    double measureTimeExecution(Func&& func, Args&&...args)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }

    template<AllowedType T>
    void testCaseMatrix(int rows_1, int cols_1, int rows_2, int cols_2)
    {
        Matrix<T> matrix_1(rows_1, cols_1);
        Matrix<T> matrix_2(rows_2, cols_2);

        fillEntityRandom(matrix_1);
        fillEntityRandom(matrix_2);

        std::cout << matrix_1 << std::endl;
        std::cout << matrix_2 << std::endl;

        std::cout << "Matrix addition result:\n";
        std::cout << matrix_1 + matrix_2;

        auto func1 = [](const auto& A, const auto& B){
            return A * B;
        };

        std::cout << measureTimeExecution(func1, matrix_1, matrix_2) << std::endl;

        auto func2 = [](const auto& A, const auto& B) {
            return multiplyMatricesParallel(A, B);
        };

        std::cout << measureTimeExecution(func2, matrix_1, matrix_2) << std::endl;
    }

    template<AllowedType T>
    void testCaseVector(int quant_1, bool is_column_1, int quant_2, bool is_column_2)
    {
        Vector<T> vector_1(quant_1, is_column_1);
        Vector<T> vector_2(quant_2, is_column_2);

        fillEntityRandom(vector_1);
        fillEntityRandom(vector_2);

        std::cout << vector_1 << std::endl;
        std::cout << vector_2 << std::endl;

        std::cout << vector_1 + vector_2 << std::endl;
    }

    template<AllowedType T>
    void testCaseMatrixVector(int rowMatrix, int colMatrix, int quant_1, bool isColumn)
    {
        Matrix<T> matrix(rowMatrix, colMatrix);
        Vector<T> vector(quant_1, isColumn);

        fillEntityRandom(matrix);
        fillEntityRandom(vector);

        std::cout << matrix << std::endl;
        std::cout << vector << std::endl;

        std::cout << matrix * vector << std::endl;
    }
}

int main()
{
    using namespace TestsInfrastructure;
    // test for all types
    {
        testCaseMatrix<int>(20, 20, 20, 20);
        testCaseMatrix<uint>(20, 20, 20, 20);
        testCaseMatrix<int8_t>(20, 20, 20, 20);
        testCaseMatrix<uint8_t>(20, 20, 20, 20);
        testCaseMatrix<int16_t>(20, 20, 20, 20);
        testCaseMatrix<uint16_t>(20, 20, 20, 20);
        testCaseMatrix<int32_t>(20, 20, 20, 20);
        testCaseMatrix<uint32_t>(20, 20, 20, 20);
        testCaseMatrix<int64_t>(20, 20, 20, 20);
        testCaseMatrix<uint64_t>(20, 20, 20, 20);
        testCaseMatrix<float>(20, 20, 20, 20);
        testCaseMatrix<double>(20, 20, 20, 20);
    }

    //test for wrong size
    {
        try
        {
            testCaseMatrix<int>(20, 23, 21, 33);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        try
        {
            testCaseMatrix<int>(-3, 12, -2, 34);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    //vector
    {
        testCaseVector<int>(3, true, 3, true);
        testCaseVector<uint>(3, true, 3, true);
        testCaseVector<int8_t>(3, true, 3, true);
        testCaseVector<uint8_t>(3, true, 3, true);
        testCaseVector<int16_t>(3, true, 3, true);
        testCaseVector<uint16_t>(3, true, 3, true);
        testCaseVector<int32_t>(3, true, 3, true);
        testCaseVector<uint32_t>(3, true, 3, true);
        testCaseVector<int64_t>(3, true, 3, true);
        testCaseVector<uint64_t>(3, true, 3, true);

        testCaseVector<int>(23, true, 23, true);

        testCaseVector<int>(3, false, 3, false);
        testCaseVector<int>(13, false, 13, false);
    }

    //test for wrong size
    {
        try
        {
            testCaseVector<int>(3, false, 3, true);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        try
        {
            testCaseVector<int>(-3, false, 3, true);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        try
        {
            testCaseVector<int>(-3, false, 234, false);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    //matrix vector
    {
        testCaseMatrixVector<int>(3, 3, 3, true);
        testCaseMatrixVector<int>(3, 3, 3, false);
        testCaseMatrixVector<int>(10, 10, 10, false);
    }

    //test for wrong size
    {
        try
        {
            testCaseMatrixVector<int>(-3, 3, 3, true);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        try
        {
            testCaseMatrixVector<int>(-3, 3, -33, true);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        try
        {
            testCaseMatrixVector<int>(3, 3, 12, false);
        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    return 0;
}