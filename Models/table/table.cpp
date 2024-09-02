#include "table.h"

Table::Table(Database &_db, std::string name) : db(_db), nameTable(name), fields(){};

std::string Table::getNameTable() const
{
    return nameTable;
}

std::vector<std::pair<std::string, std::string>> Table::getForeignKeys() const
{
    return foreignKeys;
}

void Table::setRecords(const std::vector<std::vector<std::string>> &newRecords)
{
    records = newRecords;
}

void Table::setForeignKeys(const std::vector<std::pair<std::string, std::string>> &newForeignKeys)
{
    foreignKeys = newForeignKeys;
}

void Table::setNameTable(const std::string &newNameTable)
{
    nameTable = newNameTable;
}

void Table::addField(const std::string &_namefield, Field::VALUE_type _val, int _sizeField, bool _primaryKeyField, bool _notNullField)
{
    // Проверяем, что имя поля уникально в таблице
    for (const auto &field : fields)
    {
        if (field.getFieldName() == _namefield)
        {
            std::cerr << "Поле с именем '" << _namefield << "' уже существует в таблице '" << nameTable << "'.\n";
            return;
        }
    }

    Field newField(_namefield, _val, _sizeField, _primaryKeyField, _notNullField);

    fields.push_back(newField);
}

void Table::deleteField(std::string _namefield)
{
    fields.erase(std::remove_if(fields.begin(), fields.end(),
                                [&_namefield](const Field &field)
                                {
                                    return field.getFieldName() == _namefield;
                                }),
                 fields.end());
}

Field &Table::getFieldbyName(std::string _namefield)
{
    for (auto &field : fields)
    {
        if (field.getFieldName() == _namefield)
        {
            return field;
        }
    }

    throw std::runtime_error("Field not found");
}
void Table::printTable()
{
    std::cout << "Table: " << nameTable << std::endl;
    if (fields.empty())
    {
        std::cout << "Table " << nameTable << " is empty." << std::endl;
        return;
    }
    for (Field &field : fields)
    {
        field.printField();
    }
}

void Table::printTableValue()
{
    // Проверяем, что таблица не пуста
    if (records.empty())
    {
        std::cout << "Таблица " << nameTable << " не содержит записей." << std::endl;
        return;
    }

    // Выводим подписи полей
    std::cout << "Значения записей в таблице " << nameTable << ":" << std::endl;
    for (const Field &field : fields)
    {
        std::cout << field.getFieldName() << "\t";
    }
    std::cout << std::endl;

    // Выводим значения всех записей
    for (const std::vector<std::string> &record : records)
    {
        for (const std::string &value : record)
        {
            std::cout << value << "\t";
        }
        std::cout << std::endl;
    }
}

void Table::addForeignKey(const std::string &localField, const std::string &foreignTable, const std::string &foreignField)
{
    foreignKeys.push_back(std::make_pair(localField, foreignTable + "-" + foreignField));
}

void Table::removeForeignKey(const std::string &localField)
{
    foreignKeys.erase(std::remove_if(foreignKeys.begin(), foreignKeys.end(),
                                     [&localField](const std::pair<std::string, std::string> &key)
                                     {
                                         return key.first == localField;
                                     }),
                      foreignKeys.end());
}

bool Table::hasForeignKey(const std::string &localField) const
{
    for (const auto &key : foreignKeys)
    {
        if (key.first == localField)
        {
            return true;
        }
    }
    return false;
}

void Table::printForeignKeys()
{
    for (const auto &key : foreignKeys)
    {
        std::cout << "Внешний ключ: " << key.first << " -> " << key.second << std::endl;
    }
}

std::vector<std::vector<std::string>>  Table::getRecords() const
{
    return records;
}

void Table::addRecord(const std::vector<std::pair<std::string, std::string>> &record)
{
    if (record.size() != fields.size())
    {
        std::cerr << "Ошибка: Неправильное количество значений для добавления записи." << std::endl;
        return;
    }

    // Создаем запись
    std::vector<std::string> values;
    for (const Field &field : fields)
    {
        // Получаем значение для соответствующего поля из переданной записи
        std::string fieldValue = "";
        for (const auto &pair : record)
        {
            if (pair.first == field.getFieldName())
            {
                fieldValue = pair.second;
                break;
            }
        }
        // Устанавливаем значение для поля
        const_cast<Field &>(field).setValue(fieldValue);
        // Получаем значение поля в виде строки и добавляем его к записи
        values.push_back(fieldValue);
    }

    // Проверяем ограничения целостности, если есть внешние ключи
    for (const auto &foreignKey : foreignKeys)
    {
        std::string localField = foreignKey.first;
        std::string foreignTable = foreignKey.second.substr(0, foreignKey.second.find("-"));
        std::string foreignField = foreignKey.second.substr(foreignKey.second.find("-") + 1);

        // Получаем значение поля, на которое ссылается внешний ключ
        std::string foreignValue = "";
        for (const auto &pair : record)
        {
            if (pair.first == localField)
            {
                foreignValue = pair.second;
                break;
            }
        }

        // Проверяем, что значение поля существует в связанной таблице
        try
        {
            Table &linkedTable = db.getTable(foreignTable);
            const Field &linkedField = linkedTable.getFieldbyName(foreignField);

            bool matchFound = false;
            for (const auto &linkedRecord : linkedTable.getRecords())
            {
                if (linkedRecord[linkedTable.getFieldIndex(linkedField.getFieldName())] == foreignValue)
                {
                    matchFound = true;
                    break;
                }
            }

            if (!matchFound)
            {
                throw std::runtime_error("Значение внешнего ключа не найдено в связанной таблице.");
                return;
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Ошибка при проверке внешнего ключа: " << e.what() << std::endl;
            return;
        }
    }

    // Добавляем запись
    records.push_back(values);
}

int Table::getFieldIndex(const std::string &fieldName) const
{
    for (size_t i = 0; i < fields.size(); ++i)
    {
        if (fields[i].getFieldName() == fieldName)
        {
            return i;
        }
    }

    // Если поле не найдено, можно бросить исключение или вернуть некоторое специальное значение, например, -1
    // В данном случае вернем -1
    return -1;
}

std::vector<Field> Table::getFields() const
{
    return fields;
}
void Table::saveToFile(std::ofstream &file)
{
    file << nameTable << '\n';
    file << fields.size() << '\n';
    for (auto &field : fields)
    {
        field.saveToFile(file);
    }

    if (!foreignKeys.empty())
    {
        file << foreignKeys.size() << '\n';
        for (const auto &fk : foreignKeys)
        {
            file << fk.first << " " << fk.second << '\n';
        }
    }
    else
    {
        file << foreignKeys.size() << '\n';
    }

    file << records.size() << '\n'; // Сохраняем размер вектора записей
    for (const auto &record : records)
    {
        for (const auto &field : record)
        {
            file << field << ' ';
        }
        file << '\n';
    }
}

void Table::loadFromFile(std::ifstream &file)
{
    std::string line;
    std::getline(file, line);
    nameTable = line;

    int numFields;
    file >> numFields;
    file.ignore();

    fields.clear();
    for (int i = 0; i < numFields; ++i)
    {
        Field field;
        field.loadFromFile(file);
        fields.push_back(field);
    }

    int numForeignKeys;
    file >> numForeignKeys;
    file.ignore();

    if (numForeignKeys > 0)
    {
        foreignKeys.clear();
        for (int i = 0; i < numForeignKeys; ++i)
        {
            std::string localField, foreignKey;
            std::getline(file, localField, ' ');
            std::getline(file, foreignKey, '\n');
            foreignKeys.push_back(std::make_pair(localField, foreignKey));
        }
    }

    int numRecords;
    file >> numRecords;
    file.ignore();

    records.clear(); // Очищаем вектор записей перед загрузкой
    for (int i = 0; i < numRecords; ++i)
    {
        std::getline(file, line);
        std::istringstream iss(line);
        std::vector<std::string> record;
        std::string field;
        while (iss >> field)
        {
            record.push_back(field);
        }
        records.push_back(record);
    }
}

void Table::setName(std::string newName)
{
    nameTable = newName;
}

void Table::editField(const std::string &fieldName, Field::VALUE_type newVal, int newSize, bool newPrimaryKey, bool newNotNull)
{
    auto it = std::find_if(fields.begin(), fields.end(), [&fieldName](const Field &f)
                           { return f.getFieldName() == fieldName; });
    if (it == fields.end())
    {
        throw std::runtime_error("Field does not exist.");
    }

    Field &field = *it;

    field.setType(newVal);
    field.setSizeField(newSize);
    field.setPrimaryKey(newPrimaryKey);
    field.setNotNull(newNotNull);
}
