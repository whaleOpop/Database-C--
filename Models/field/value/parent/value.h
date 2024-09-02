#ifndef VALUE_H
#define VALUE_H

#include <string>

class Value {
public:
  
    virtual std::string getType() const = 0;
    virtual int getSize() const = 0;
    virtual std::string getValue() const = 0;
};
#endif