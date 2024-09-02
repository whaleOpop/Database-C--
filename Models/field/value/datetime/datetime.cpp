#include "datetime.h"

DateTime::DateTime(int sz, const std::string &val) : size(sz), value(val) {}
std::string DateTime::getType() const { return "datetime"; }
int DateTime::getSize() const { return size; }
std::string DateTime::getValue() const { return value; }