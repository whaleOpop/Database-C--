#ifndef BIT_H
#define BIT_H

#include "../parent/value.h"

class Bit : public Value
{
private:
    int size;
    bool value;

public:
    Bit(int sz, bool val);
    Bit() : size(0), value(0) {}
    virtual std::string getType() const override;
    virtual int getSize() const override;
    virtual std::string getValue() const override;
};

#endif