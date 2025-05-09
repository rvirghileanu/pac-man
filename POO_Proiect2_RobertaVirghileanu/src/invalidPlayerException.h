#pragma once
#include <stdexcept>
#include <string>

class InvalidPlayerPositionException : public std::exception {
    std::string message;
public:
    InvalidPlayerPositionException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};
