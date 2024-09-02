#ifndef INT_H
#define INT_H

#include "../parent/value.h"

class Int : public Value {
private:
    int size;
    int value;
public:
    Int(int sz, int val);
    Int() : size(0), value(0) {};
    virtual std::string getType() const override;
    virtual int getSize() const override;
    virtual std::string getValue() const override;
};

#endif