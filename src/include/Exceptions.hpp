#pragma once
#include <exception>
#include <string>

#define PROJECT_EXCEPTION(ExceptionName, ExceptionParent, message)                                                \
    class ExceptionName : public ExceptionParent                                                                  \
    {                                                                                                             \
    public:                                                                                                       \
        ExceptionName() = default;                                                                                \
        explicit ExceptionName(const std::string& msg) : ExceptionParent(std::string(message) + " " + msg) {}     \
    };

class BaseException : public std::exception
{
public:
    BaseException() = default;
    explicit BaseException(std::string&& msg) : m_ErrorInfo(std::move(msg)) {}

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_ErrorInfo.c_str();
    }

    [[nodiscard]] const std::string& GetInfo() const noexcept
    {
        return m_ErrorInfo;
    }

private:
    std::string m_ErrorInfo;
};

PROJECT_EXCEPTION(SizeException, BaseException, "(Incorrect matrix or vector size)")
PROJECT_EXCEPTION(IncompatibleSizeException, BaseException, "(Not equal sizes of matrices or vectors)")
PROJECT_EXCEPTION(IndexException, BaseException, "(Forbidden index of matrix or vector)")