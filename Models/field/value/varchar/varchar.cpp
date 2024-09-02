#include "varchar.h"

Varchar::Varchar(int sz, const std::string &val) : size(sz), value(val) {}
std::string Varchar::getType() const { return "varchar"; }
int Varchar::getSize() const { return size; }
std::string Varchar::getValue() const { return value; }