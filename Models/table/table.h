
#ifndef TABLE_H
#define TABLE_H

#include "../field/field.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <map>
#include "../datebase/datebase.h"

class Database;
class Table
{
private:
    std::string nameTable;
    std::vector<Field> fields;
    std::vector<std::pair<std::string, std::string>> foreignKeys;
    std::vector<std::vector<std::string>> records;
    Database &db;

public:
    Table &operator=(const Table &other)
    {
        if (this != &other)
        {
            this->nameTable = other.nameTable;
            this->fields = other.fields;
            this->foreignKeys = other.foreignKeys;
            this->records = other.records;
            
        }
        return *this;
    }

    Table(Database &_db, std::string name);

    void addField(const std::string &_namefield, Field::VALUE_type _val, int _sizeField, bool _primaryKeyField, bool _notNullField);
    void deleteField(std::string _namefield);

    void updateTable();

    void readTable();

    void printTable();

    void printTableValue();

    Field &getFieldbyName(std::string _namefield);

    std::string getNameTable() const;

    void addForeignKey(const std::string &localField, const std::string &foreignTable, const std::string &foreignField);
   

    void removeForeignKey(const std::string &localField);
    void printForeignKeys();
    bool hasForeignKey(const std::string& localField) const ;

    void addRecord(const std::vector<std::pair<std::string, std::string>> &record);

    std::vector<std::vector<std::string>> getRecords() const;

    std::vector<Field> getFields() const;

    int getFieldIndex(const std::string &fieldName) const;

    void saveToFile(std::ofstream &file);
    void loadFromFile(std::ifstream &file);

    void setName(std::string newName);
    void editField(const std::string &fieldName, Field::VALUE_type newVal, int newSize, bool newPrimaryKey, bool newNotNull);

    void setNameTable(const std::string &newNameTable);
    std::vector<std::pair<std::string, std::string>> getForeignKeys() const;
    void setForeignKeys(const std::vector<std::pair<std::string, std::string>> &newForeignKeys);

    void setRecords(const std::vector<std::vector<std::string>> &newRecords);
};

#endif
