#ifndef FIELD_H
#define FIELD_H

#include "string"
#include "iostream"
#include "value/parent/value.h"
#include "value/bit/bit.h"
#include "value/int/int.h"
#include "value/varchar/varchar.h"
#include "value/datetime/datetime.h"
#include "vector"
#include <fstream>
#include <sstream>
#include <memory>

class Field
{
public:
    enum VALUE_type
    {
        INTEGER,
        DATETIME,
        VARCHAR,
        BIT
    } val;

private:
    std::string nameField;
    bool primaryKeyField;
    int sizeField;
    bool notNullField;

    std::vector<std::shared_ptr<Value>> values;
    void setTypeValue(VALUE_type val);

public:
    Field(std::string _namefield, VALUE_type val, int _sizeField, bool _primaryKeyField, bool _notNullField);
    Field() : val(INTEGER), nameField(""), primaryKeyField(false), sizeField(0), notNullField(false){};
    Field(const std::string &serializedData);

    void createField();
    void updateField();
    void deleteField();
    void readField();
    void printField();

    std::string getNameField() const;
    VALUE_type getType() const;
    int getSizeField() ;
    bool isPrimaryKey() ;
    bool isNotNull() ;

    void setNameField(const std::string &nameField);
    void setType(VALUE_type val);
    void setSizeField(int sizeField);
    void setPrimaryKey(bool primaryKeyField);
    void setNotNull(bool notNullField);

    std::string setNameField();
    bool setPrimaryKeyField();
    int setSizeField();
    void setValue(const std::string &value);
    void addValue(int value);
    void addValue(std::string value);
    void addValue(bool value);
    std::string getFieldName() const;

    void saveToFile(std::ofstream &file);
    void loadFromFile(std::ifstream &file);
};

#endif