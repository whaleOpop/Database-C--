#include "int.h"

Int::Int(int sz, int val) : size(sz), value(val) {}
std::string Int::getType() const { return "int"; }
int Int::getSize() const { return size; }
std::string Int::getValue() const { return std::to_string(value); }