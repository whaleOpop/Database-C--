

#include "bit.h"

Bit::Bit(int sz, bool val):size{sz},value{val}{};

std::string Bit::getType() const {
    return "bit";
}

int Bit::getSize() const {
    return size;
}

std::string Bit::getValue() const {
    return value ? "true" : "false";
}
