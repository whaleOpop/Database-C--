#ifndef VARCHAR_H
#define VARCHAR_H

#include "../parent/value.h"

class Varchar : public Value
{
private:
    int size;
    std::string value;

public:
    Varchar(int sz, const std::string &val);
    Varchar() : size(0), value("") {};
    virtual std::string getType() const override;
    virtual int getSize() const override;
    virtual std::string getValue() const override;
};
#endif