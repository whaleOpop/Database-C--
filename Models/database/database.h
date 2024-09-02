
#ifndef DATEBASE_H
#define DATEBASE_H

#include "string"
#include "vector"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdexcept>
#include <direct.h>
#include <filesystem>
#include <algorithm>
#include "../table/table.h"
class Table;
class Database
{

private:
    std::string nameField;
    std::vector<Table> tables;
    void createFile(std::string _nameField);
    
    void deleteFile(std::string _nameField);
    void copyFile(const std::string &srcFilePath, const std::string &destFilePath);
    void copyFolder(const std::string &srcFolderPath, const std::string &destFolderPath);
    void editFile(std::string _oldNameField, std::string _nameField);

public:
    Database(std::string _nameField);
    Database();
    ~Database();
    std::string getName();
    void editDatebase(std::string _nameField);
    void readDatebase();
    void printDatebase();
    void printDatebaseValue();
    void addTable(std::string _nameTable);
    void deleteFile();

    void deleteTable(std::string _nameTable);
    void updateTableName(const std::string &oldName, const std::string &newName);
    void updateTable(const Table &oldTable, const Table &newTable);
    void editTable();

    Table &getTable(const std::string &tableName);

    const std::vector<Table> &getTables() const;

    void addRecordToTable(const std::string &tableName, const std::vector<std::pair<std::string, std::string>> &record);

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);
};

#endif