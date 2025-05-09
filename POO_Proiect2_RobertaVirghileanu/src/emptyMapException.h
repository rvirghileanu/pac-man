#pragma once
#include <stdexcept>
#include <string>

class EmptyMapFileException : public std::exception {
    std::string message;
public:
    EmptyMapFileException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
