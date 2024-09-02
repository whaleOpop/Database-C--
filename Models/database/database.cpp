#include "database.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <direct.h>

Database::Database(std::string _nameField) : nameField{_nameField}, tables{}
{
    createFile(_nameField);
}


Database::Database() : nameField(""), tables{} {};

Database::~Database()
{
}
const std::vector<Table> &Database::getTables() const
{
    return tables;
}

std::string Database::getName()
{
    return nameField;
}

void Database::createFile(std::string _nameField)
{
    std::string databasePath = _nameField + "/";

    struct stat info;
    if (stat(databasePath.c_str(), &info) != 0)
    {
        if (_mkdir(databasePath.c_str()) != 0)
        {
            std::cerr << "Ошибка: Не удалось создать папку DatabaseL.\n";
            return;
        }
    }
    else if (!(info.st_mode & S_IFDIR))
    {
        std::cerr << "Ошибка: DatabaseL не является директорией.\n";
        return;
    }

    std::string filePath = databasePath + _nameField + ".txt";

    if (stat(filePath.c_str(), &info) == 0)
    {
        std::cerr << "Файл уже существует. Не заменяем его содержимое.\n";
        return;
    }

    std::ofstream MyFile(filePath);

    if (!MyFile.is_open())
    {
        std::cerr << "Не удалось открыть файл для записи.\n";
        return;
    }

    MyFile.close();
    if (!MyFile)
    {
        std::cerr << "Ошибка при закрытии файла.\n";
        return;
    }
}

void Database::deleteFile()
{
    std::string filePath = nameField + "/" + nameField + ".txt";

    if (remove(filePath.c_str()) != 0)
    {
        std::cerr << "Ошибка: Не удалось удалить файл " << filePath << ".\n";
    }

    if (_rmdir(nameField.c_str()) != 0)
    {
        std::cerr << "Ошибка: Не удалось удалить папку " << nameField << ".\n";
    }
}

void Database::deleteFile(std::string _nameField)
{
    std::string filePath = _nameField + "/" + _nameField + ".txt";

    if (remove(filePath.c_str()) != 0)
    {
        std::cerr << "Ошибка: Не удалось удалить файл " << filePath << ".\n";
    }

    if (_rmdir(_nameField.c_str()) != 0)
    {
        std::cerr << "Ошибка: Не удалось удалить папку " << _nameField << ".\n";
    }
}

void Database::copyFile(const std::string &srcFilePath, const std::string &destFilePath)
{
    std::ifstream sourceFile(srcFilePath, std::ios::binary);
    std::ofstream destFile(destFilePath, std::ios::binary);
    destFile << sourceFile.rdbuf();
}

void Database::editFile(std::string _oldNameField, std::string _nameField)
{
    createFile(_nameField);

    std::string oldFilePath = _oldNameField + "/" + _oldNameField + ".txt";
    std::string newFilePath = _nameField + "/" + _nameField + ".txt";

    copyFile(oldFilePath, newFilePath);

    deleteFile(_oldNameField);
    nameField = _nameField;
}

void Database::editDatebase(std::string _nameField)
{
    editFile(nameField, _nameField);
}

void Database::addTable(std::string _nameTable)
{
    for (const auto &table : tables)
    {
        if (table.getNameTable() == _nameTable)
        {
            std::cerr << "Таблица с таким именем уже существует";
            return;
        }
    }

    tables.push_back(Table(*this, _nameTable));
}

void Database::deleteTable(std::string _nameTable)
{
    tables.erase(std::remove_if(tables.begin(), tables.end(),
                                [&_nameTable](const Table &table)
                                {
                                    return table.getNameTable() == _nameTable;
                                }),
                 tables.end());
}

Table &Database::getTable(const std::string &tableName)
{
    for (auto &table : tables)
    {
        if (table.getNameTable() == tableName)
        {
            return table;
        }
    }
    throw std::runtime_error("Таблица не найдена");
}

void Database::printDatebase()
{
    std::cout << "Функция printDatebase вызвана." << std::endl;
    if (tables.empty())
    {
        std::cout << "В базе данных нет таблиц." << std::endl;
        return;
    }
    std::cout << "В базе данных содержится " << tables.size() << " таблиц." << std::endl;
    for (auto &table : tables)
    {
        if (&table == nullptr)
        {
            std::cout << "Указатель на таблицу равен null." << std::endl;
            continue;
        }
        table.printTable();
        table.printForeignKeys();
        std::cout << std::endl;
    }
}

void Database::printDatebaseValue()
{
    std::cout << "Функция printDatebaseValue вызвана." << std::endl;
    if (tables.empty())
    {
        std::cout << "В базе данных нет таблиц." << std::endl;
        return;
    }
    std::cout << "В базе данных содержится " << tables.size() << " таблиц." << std::endl;
    for (auto &table : tables)
    {
        if (&table == nullptr)
        {
            std::cout << "Указатель на таблицу равен null." << std::endl;
            continue;
        }
        table.printTableValue();

        std::cout << std::endl;
    }
}

void Database::addRecordToTable(const std::string &tableName, const std::vector<std::pair<std::string, std::string>> &record)
{
    try
    {
        Table &table = getTable(tableName);
        table.addRecord(record);
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

void Database::updateTableName(const std::string &oldName, const std::string &newName)
{
    for (auto &table : tables)
    {
        if (table.getNameTable() == oldName)
        {
            table.setName(newName);
            break;
        }
    }
}

void Database::updateTable(const Table &oldTable, const Table &newTable)
{
    for (auto &table : tables)
    {
        if (table.getNameTable() == oldTable.getNameTable())
        {
            table = oldTable;
            break;
        }
    }
}

void Database::saveToFile(std::string filename)
{
    std::ofstream file(filename + "/" + filename + ".txt");
    if (file.is_open())
    {
        file << nameField << std::endl;
        for (auto &table : tables)
        {
            file << table.getNameTable() << std::endl;
            table.saveToFile(file);
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
    }
}

void Database::loadFromFile(std::string filename)
{
    std::ifstream file(filename + "/" + filename + ".txt");
    if (file.is_open())
    {
        // Clear existing tables
        tables.clear();

        std::string line;
        std::getline(file, nameField);
        while (std::getline(file, line))
        {
            Table table(*this, line);
            table.loadFromFile(file);
            tables.push_back(table);
        }

        file.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading: " << filename << std::endl;
    }
}