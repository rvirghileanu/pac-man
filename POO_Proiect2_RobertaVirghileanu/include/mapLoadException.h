#pragma once
#include "GameException.h"

class MapLoadException : public GameException {
public:
    explicit MapLoadException(const std::string& msg)
        : GameException("MapLoadException: " + msg) {}
};
