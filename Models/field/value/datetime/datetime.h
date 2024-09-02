#ifndef DATETIME_H
#define DATETIME_H

#include "../parent/value.h"
class DateTime : public Value
{
private:
    int size;
    std::string value;

public:
    DateTime(int sz, const std::string &val);
    DateTime() : size(0), value("") {}
    virtual std::string getType() const override;
    virtual int getSize() const override;
    virtual std::string getValue() const override;
};

#endif