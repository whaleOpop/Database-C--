#include "main.h"

bool isNumber(const std::string &str)
{
    std::istringstream iss(str);
    int num;
    if (!(iss >> num))
    {
        return false;
    }
    return true;
}

void addTable(Database &db)
{

    std::cout << "Введите название таблицы:" << std::endl;
    std::string nameTable;
    do
    {
        std::cin >> nameTable;
    } while (nameTable == "");
    db.addTable(nameTable);
    Table &table = db.getTable(nameTable);
    std::cout << "Введите кол-во полей:" << std::endl;
    int count = 0;
    std::cin >> count;

    for (int i = 0; i < count; i++)
    {
        std::cout << "Введите название поля:" << std::endl;
        std::string nameField;
        do
        {
            std::cin >> nameField;
        } while (nameField == "");

        std::cout << "Выберите тип данных поля:" << std::endl;
        std::cout << "1) INTEGER" << std::endl;
        std::cout << "2) DATETIME" << std::endl;
        std::cout << "3) VARCHAR" << std::endl;
        std::cout << "4) BIT" << std::endl;
        std::string typeStr;
        int val = 0;
        std::cin >> val;
        Field::VALUE_type vals;
        switch (val)
        {
        case 1:
            vals = Field::INTEGER;
            break;

        case 2:
            vals = Field::DATETIME;
            break;

        case 3:
            vals = Field::VARCHAR;
            break;

        case 4:
            vals = Field::BIT;
            break;

        default:
            vals = Field::VALUE_type(val);
            break;
        }

        std::cout << "Введите размер поля:" << std::endl;
        int size = 0;
        do
        {
            std::cin >> size;
        } while (size <= 0);

        std::cout << "Это ключёвое поле?(1,0):" << std::endl;
        bool prk = false;
        do
        {
            std::cin >> prk;
        } while (prk != true && prk != false);

        std::cout << "Это NotNull поле?(1,0):" << std::endl;
        bool notnull = false;
        do
        {
            std::cin >> notnull;
        } while (notnull != true && notnull != false);
        table.addField(nameField, vals, size, prk, notnull);
    }
    db.saveToFile(db.getName());
}
void editTable(Database &db)
{
    std::vector<Table> tables = db.getTables();
    if (!tables.empty())
    {

        for (size_t i = 0; i < tables.size(); i++)
        {
            std::cout << i + 1 << ") " << std::endl;
            tables[i].printTable();
        }
        int choice = 0;
        std::cout << "Выберите таблицу, которую хотите редактировать" << std::endl;
        std::cin >> choice;
        system("cls");
        Table &table = tables[choice - 1];
        table.printTable();
        std::cout << "Хотите изменить имя? y/n" << std::endl;

        std::string choiceYn;
        do
        {
            std::cin >> choiceYn;
        } while ((choiceYn != "n") && (choiceYn != "y"));

        if (choiceYn == "y")
        {

            std::cout << "Введите новое имя таблицы" << std::endl;
            std::string newNameTable;
            std::string oldName = table.getNameTable();
            do
            {
                std::cin >> newNameTable;
            } while (newNameTable == "");
            table.setName(newNameTable);

            db.updateTableName(oldName, newNameTable);

            system("cls");
            std::cout << "Имя обновлено " << newNameTable << std::endl;
            table.printTable();
        }
        else
        {
            std::cout << "Вы выбрали не изменять имя." << std::endl;
        }
        std::cout << "Хотите изменить поля таблицы? y/n" << std::endl;
        choiceYn = "";
        do
        {
            std::cin >> choiceYn;
        } while ((choiceYn != "n") && (choiceYn != "y"));

        if (choiceYn == "y")
        {
            std::cout << "Введите название поля для редактирования:" << std::endl;
            std::string fieldName;
            std::cin >> fieldName;
            std::cout << "Введите новый тип данных поля:" << std::endl;
            std::cout << "Выберите тип данных поля:" << std::endl;
            std::cout << "1) INTEGER" << std::endl;
            std::cout << "2) DATETIME" << std::endl;
            std::cout << "3) VARCHAR" << std::endl;
            std::cout << "4) BIT" << std::endl;
            std::string typeStr;
            int val = 0;
            std::cin >> val;
            Field::VALUE_type vals;
            switch (val)
            {
            case 0:
                vals = Field::VALUE_type(val);
                break;

            case 1:
                vals = Field::VALUE_type(val);
                break;

            case 2:
                vals = Field::VALUE_type(val);
                break;

            case 3:
                vals = Field::VALUE_type(val);
                break;

            default:
                vals = Field::VALUE_type(val);
                break;
            }

            std::cout << "Введите новый размер поля:" << std::endl;
            int newSize;
            std::cin >> newSize;
            std::cout << "Это ключевое поле?(1,0):" << std::endl;
            bool newPrimaryKey;
            std::cin >> newPrimaryKey;
            std::cout << "Это NotNull поле?(1,0):" << std::endl;
            bool newNotNull;
            std::cin >> newNotNull;
            table.editField(fieldName, vals, newSize, newPrimaryKey, newNotNull);
            db.updateTable(table, table);
            table.printTable();
            db.saveToFile(db.getName());
        }
        else
        {
            std::cout << "Вы выбрали не редактировать поля." << std::endl;
        }

        db.saveToFile(db.getName());
    }
    else
    {
        std::cout << "В этой базе нет таблиц для редактирования" << std::endl;
    }
}

void printDB(Database &db)
{
    std::string choice;
    db.printDatebase();
    std::cout << "Нажмите любую клавишу для того чтобы вернуться назад" << std::endl;
    std::cin >> choice;
    getchar();
}

void deleteTable(Database &db)
{
    std::vector<Table> tables = db.getTables();
    if (!tables.empty())
    {
        for (size_t i = 0; i < tables.size(); i++)
        {
            std::cout << i + 1 << ") " << std::endl;
            tables[i].printTable();
        }
        int choice = 0;
        std::cout << "Выберите таблицу которую хотите удалить" << std::endl;

        std::cin >> choice;

        Table &table = tables[choice - 1];

        db.deleteTable(table.getNameTable());
        db.saveToFile(db.getName());

        std::cout << "Таблица удалена : " << table.getNameTable() << std::endl;
    }
    else
    {
        std::cout << "Нет таблиц для удаления" << std::endl;
    }
}

void addForeign(Database &db)
{
    std::cout << "Добавление внешних ключей" << std::endl;
    std::vector<Table> tables = db.getTables();
    if (!tables.empty())
    {

        for (size_t i = 0; i < tables.size(); i++)
        {

            std::cout << i + 1 << ") " << std::endl;
            tables[i].printTable();
        }

        int choiceT1 = 0;
        std::cout << "Выберите таблицу которой хотите добавить внешнию связь" << std::endl;
        std::cin >> choiceT1;
        // Clearing the console in a cross-platform way
        std::cout << std::string(100, '\n');
        Table &table = tables[choiceT1 - 1];

        std::vector<Field> fields = table.getFields();
        table.printTable();

        std::string choiceFieldT1;
        std::cout << "Введите имя поля" << std::endl;
        std::cin >> choiceFieldT1;
        std::cout << std::string(100, '\n');

        int choiceT2 = 0;
        std::cout << "Выберите таблицу с которой хотите связать таблицу" << std::endl;

        for (size_t i = 0; i < tables.size(); i++)
        {
            if (i != (choiceT1 - 1))
            {
                std::cout << i + 1 << ") " << std::endl;
                tables[i].printTable();
            }
        }

        std::cin >> choiceT2;
        Table &table2 = tables[choiceT2 - 1];
        std::cout << std::string(100, '\n');
        std::string choiceFieldT2;
        std::cout << "Введите имя поля связующей таблицы" << std::endl;
        table2.printTable();
        std::cin >> choiceFieldT2;

        table.addForeignKey(choiceFieldT1, table2.getNameTable(), choiceFieldT2);

        db.updateTable(table, table);
        db.printDatebase();
        db.saveToFile(db.getName());
    }
    else
    {
        std::cout << "Нет таблиц для добавления внешних ключей" << std::endl;
    }
}
void editDataDb(Database &db);
// vrode done
void deleteForeign(Database &db)
{
    std::vector<Table> tables = db.getTables();
    if (!tables.empty())
    {

        std::string choice;
        bool validChoice = false;
        int preSize = 0;
        do
        {
            for (size_t i = 0; i < tables.size(); i++)
            {
                if (!tables[i].getForeignKeys().empty())
                {

                    std::cout << i + 1 << ") " << std::endl;
                    std::cout << tables[i].getNameTable() << std::endl;
                    tables[i].printForeignKeys();
                    preSize++;
                }
            }
            std::cout << "Выберите таблицу которой хотите добавить внешнию связь" << std::endl;
            std::cout << "q - для выхода" << std::endl;
            std::cin >> choice;
            if (choice != "")
                if (isNumber(choice))
                {
                    if (std::stoi(choice) > 0 && std::stoi(choice) <= preSize)
                    {
                        validChoice = true;
                    }
                }
            if (choice == "q")
            {
                break;
            }
        } while (!validChoice);

        validChoice = false;

        Table &table = tables[std::stoi(choice) - 1];
        choice = "";

        do
        {
            system("cls");
            for (size_t i = 0; i < tables.size(); i++)
            {
                if (!tables[i].getForeignKeys().empty())
                {

                    if (!tables[i].getForeignKeys().empty())
                    {

                        std::cout << i + 1 << ") " << std::endl;
                        std::cout << tables[i].getNameTable() << std::endl;
                        tables[i].printForeignKeys();
                    }
                }
            }

            std::cout << "Введите поле которое хотите удалить" << std::endl;
            std::cin >> choice;
            if (choice != "")
                if (table.hasForeignKey(choice))
                {
                    validChoice = true;
                }

            if (choice == "q")
            {

                break;
            }
        } while (!validChoice);
        if (validChoice)
        {
            table.removeForeignKey(choice);
            db.updateTable(table, table);
            db.saveToFile(db.getName());
        }
    }
    else
    {
        std::cout << "Нет таблиц для удаления внешних ключей" << std::endl;
    }
    system("cls");
    std::cout << "Выберите таблицу из которой хотите удалить внешнию связь" << std::endl;
}

// done
void operTable(Database &db)
{

    std::string choice;
    bool validChoice = false;
    do
    {
        system("cls");
        std::cout << "<---Операции над таблицами--->" << std::endl;
        std::cout << "1) Добавить таблицу" << std::endl;
        std::cout << "2) Редактировать таблицу" << std::endl;
        std::cout << "3) Удалить таблицу" << std::endl;
        std::cout << "4) Назад" << std::endl;
        std::cin >> choice;
        if (isNumber(choice))
        {
            if (std::stoi(choice) > 0 && std::stoi(choice) <= 4)
            {
                validChoice = true;
            }
        }

    } while (!validChoice);

    switch (std::stoi(choice))
    {
    case 1:
        system("cls");
        addTable(db);
        break;
    case 2:
        system("cls");
        editTable(db);
        break;
    case 3:
        system("cls");
        deleteTable(db);
        break;
    case 4:
        system("cls");
        editDataDb(db);
        break;
    default:
        system("cls");
        std::cout << "Некорректный ввод. Пожалуйста, выберите от 1 до 4.\n";
    }
}
void operForeign(Database &db)
{
    std::string choice;
    bool validChoice = false;

    do
    {
        system("cls");
        std::cout << "<---Операции над внешними связими--->" << std::endl;
        std::cout << "1) Добавить внешнию связь" << std::endl;
        std::cout << "2) Удалить внешнию связь" << std::endl;
        std::cout << "3) Назад" << std::endl;
        std::cin >> choice;
        if (isNumber(choice))
        {
            int choiceInt = std::stoi(choice);
            if (choiceInt > 0 && choiceInt <= 3)
            {
                validChoice = true;
            }
        }
    } while (!validChoice);

    switch (std::stoi(choice))
    {
    case 1:
        system("cls");
        addForeign(db);
        break;
    case 2:
        system("cls");
        deleteForeign(db);
        break;
    case 3:
        system("cls");
        editDataDb(db);
        break;
    default:
        system("cls");
        std::cout << "Некорректный ввод. Пожалуйста, выберите от 1 до 3.\n";
    }
}

void deleteDB(Database &db)
{
    std::string choice;
    bool validChoice = false;
    do
    {
        std::cout << "Вы точно хотите удалить базу данных y/n" << std::endl;
        std::cout << "q - Выход" << std::endl;
        std::cin >> choice;
        if (choice != "")
        {
            validChoice = true;
            if (choice == "q")
            {
                validChoice = false;
                break;
            }
        }

    } while (!validChoice);

    if (validChoice)
    {
        if (choice == "y")
        {
            db.deleteFile();
        }
    }
}
void editDB(Database &db)
{
    std::string choice;
    bool validChoice = false;
    do
    {
        system("cls");
        std::cout << "Введите новое имя базы данных" << std::endl;
        std::cout << "q - Выход" << std::endl;
        std::cin >> choice;
        if (choice != "")
        {
            validChoice = true;
        }

        if (choice == "q")
        {
            break;
        }
    } while (!validChoice);
    if (validChoice)
    {
        db.editDatebase(choice);
        db.saveToFile(db.getName());
    }
}

void operDataBase(Database &db)
{

    std::string choice;
    bool validChoice = false;
    do
    {
        system("cls");
        std::cout << "<---Операции над данными таблицы--->" << std::endl;
        std::cout << "1) Вывести всю структуру базы данных" << std::endl;
        std::cout << "2) Изменить имя базы данных" << std::endl;
        std::cout << "3) Удалить базу данных" << std::endl;
        std::cout << "4) Назад" << std::endl;
        std::cin >> choice;
        if (isNumber(choice))
        {
            if (std::stoi(choice) > 0 && std::stoi(choice) <= 4)
            {
                validChoice = true;
            }
        }

    } while (!validChoice);

    switch (std::stoi(choice))
    {
    case 1:
        system("cls");
        printDB(db);
        break;
    case 2:
        system("cls");
        editDB(db);
        break;
    case 3:
        system("cls");
        deleteDB(db);
        break;
    case 4:
        system("cls");
        editDataDb(db);
        break;
    default:
        system("cls");
        std::cout << "Некорректный ввод. Пожалуйста, выберите от 1 до 4.\n";
    }
}
void operDataTable(Database &db);
void addRecordToTable(Database &db)
{
    std::vector<Table> tables = db.getTables();
    if (tables.empty())
    {
        std::cout << "Нет таблиц в базе данных." << std::endl;
        return;
    }

    std::cout << "Доступные таблицы:" << std::endl;
    for (size_t i = 0; i < tables.size(); ++i)
    {
        std::cout << i + 1 << ") ";
        tables[i].printTable();
    }

    int tableChoice;
    std::cout << "Выберите таблицу которую хотите запомнить: ";
    while (!(std::cin >> tableChoice) || tableChoice < 1 || tableChoice > tables.size())
    {
        std::cout << "Не правильный ввод данных: ";
        std::cin.clear();
    }

    Table &selectedTable = tables[tableChoice - 1];

    int recordCount;
    std::cout << "Введите кол-во полей которое хотите заполнить: ";
    while (!(std::cin >> recordCount) || recordCount <= 0)
    {
        std::cout << "Не правильный ввод данных: ";
        std::cin.clear();
    }

    std::vector<std::pair<std::string, std::string>> records;
    for (int i = 0; i < recordCount; ++i)
    {
        std::cout << "Введите данные формате" << i + 1 << " (format: 'key value'): ";
        std::string key, value;
        std::cin >> key >> value;
        records.push_back({key, value});
    }

    db.addRecordToTable(selectedTable.getNameTable(), records);
    db.saveToFile(db.getName());

    operDataTable(db);
}

void deleteRecordTable(Database &db)
{
    std::vector<Table> tables = db.getTables();
    if (tables.empty())
    {
        std::cout << "Нет таблиц в базе данных" << std::endl;
        return;
    }

    std::cout << "Доступные таблицы:" << std::endl;
    for (size_t i = 0; i < tables.size(); ++i)
    {
        std::cout << i + 1 << ") ";
        tables[i].printTable();
    }

    int tableChoice;
    std::cout << "Выберите таблицу которую хотите запомнить: ";
    while (!(std::cin >> tableChoice) || tableChoice < 1 || tableChoice > tables.size())
    {
        std::cout << "Не правильный ввод данных: ";
        std::cin.clear();
    }

    Table &selectedTable = tables[tableChoice - 1];

    std::vector<std::vector<std::string>> records = selectedTable.getRecords();

    for (size_t i = 0; i < records.size(); i++)
    {
        std::cout << i + 1 << ") ";
        for (const std::vector<std::string> &record : records)
        {
            for (const std::string &value : record)
            {
                std::cout << value << "\t";
                
            }
            std::cout << std::endl;
        }
    }
}
void printRecordTable(Database &db)
{
    db.printDatebaseValue();
    std::string choice;
    std::cin >> choice;
}
void operDataTable(Database &db)
{
    std::string choice;
    bool validChoice = false;
    do
    {
        system("cls");
        std::cout << "<---Операции над данными таблицы--->" << std::endl;
        std::cout << "1) Добавить данные в таблицу" << std::endl;
        std::cout << "2) Удалить данные из таблицу" << std::endl;
        std::cout << "3) Вывести данные из таблицы" << std::endl;
        std::cout << "4) Назад" << std::endl;
        std::cin >> choice;
        if (isNumber(choice))
        {
            if (std::stoi(choice) > 0 && std::stoi(choice) <= 5)
            {
                validChoice = true;
            }
        }
    } while (!validChoice);

    switch (stoi(choice))
    {
    case 1:

        system("cls");
        addRecordToTable(db);
        break;
    case 2:
        system("cls");
        deleteRecordTable(db);
        break;
    case 3:
        system("cls");
        printRecordTable(db);
        break;
    case 4:
        system("cls");
        break;
    default:
        system("cls");
        std::cout << "Некорректный ввод. Пожалуйста, выберите от 1 до 5.\n";
    }
}

void editDataDb(Database &db)
{
    std::string choice;
    bool validChoice = false;
    do
    {
        system("cls");
        std::cout << "<---" << db.getName() << "--->" << std::endl;
        std::cout << "1) Операции над таблицами" << std::endl;
        std::cout << "2) Операции над внешними св��зями" << std::endl;
        std::cout << "3) Операции над данными таблицы" << std::endl;
        std::cout << "4) Операции над базой" << std::endl;
        std::cout << "5) Назад" << std::endl;
        std::cin >> choice;
        if (isNumber(choice))
        {
            if (std::stoi(choice) > 0 && std::stoi(choice) <= 5)
            {
                validChoice = true;
            }
        }
    } while (!validChoice);

    switch (stoi(choice))
    {
    case 1:

        system("cls");
        operTable(db);
        break;
    case 2:

        system("cls");
        operForeign(db);
        break;
    case 3:

        system("cls");
        operDataTable(db);
        break;
    case 4:
        system("cls");
        operDataBase(db);
        break;
    case 5:
        system("cls");
        break;
    default:
        system("cls");
        std::cout << "Некорректный ввод. Пожалуйста, выберите от 1 до 5.\n";
    }
}

std::vector<std::string> getDirectoryNames()
{
    std::vector<std::string> directories;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*", &findFileData);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0)
                {
                    directories.push_back(findFileData.cFileName);
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
    }
    else
    {
        std::cerr << "Ошибка при открытии базы данных\n";
    }

    return directories;
}

// done
void editDb()
{
    std::vector<std::string> directories = getDirectoryNames();

    if (directories.empty())
    {
        std::cout << "Базы данных не найдены.\n";
        return;
    }

    std::string choice;
    bool validChoice = false;
    do
    {
        system("cls");
        std::cout << "Выберите базу данных" << std::endl;
        for (size_t i = 0; i < directories.size(); ++i)
        {
            std::cout << i + 1 << ") " << directories[i] << std::endl;
        }
        std::cin >> choice;
        if (isNumber(choice))
        {
            if (std::stoi(choice) > 0 && std::stoi(choice) <= directories.size())
            {
                validChoice = true;
            }
        }
    } while (!validChoice);

    if (validChoice)
    {
        std::string selectedDirectory = directories[std::stoi(choice) - 1];
        Database db;
        db.loadFromFile(selectedDirectory);
        system("cls");
        editDataDb(db);
    }
    else
    {
        std::cout << "Некорректный выбор. Пожалуйста, выберите номе�� базы данных.\n";
    }
}

void createDb()
{
    std::cout << "Введете название базы данных\n";
    std::cout << "q - Назад\n";
    std::string nameDb;
    bool isDirectoryExists = false;
    do
    {
        isDirectoryExists = false;
        std::cin >> nameDb;
        system("cls");

        std::vector<std::string> directories = getDirectoryNames();

        for (const auto &directory : directories)
        {
            if (directory == nameDb)
            {
                isDirectoryExists = true;
                break;
            }
        }

        if (isDirectoryExists)
        {
            std::cout << "Вы уже имеете базу данных с таким именем.\n";
        }

    } while (nameDb == "q" || nameDb.empty() || isDirectoryExists);

    Database db(nameDb);
    db.saveToFile(nameDb);
    std::cout << "База данных " << nameDb << " успешно создана.\n";
    db.loadFromFile(nameDb);
    editDataDb(db);
}

// done
void showMainMenu(bool *prtExit)
{

    std::string choice;
    do
    {
        system("cls");
        std::cout << "<---WhaleOpop-DB--->" << std::endl;
        std::cout << "1) Создать Базу данных\n";
        std::cout << "2) Редактировать Существующую\n";
        std::cout << "3) Выход\n";
        std::cin >> choice;
    } while (!isNumber(choice));

    switch (std::stoi(choice))
    {
    case 1:
        system("cls");
        createDb();
        break;
    case 2:
        system("cls");
        editDb();
        break;
    case 3:
        *prtExit = true;
        break;
    default:
        system("cls");
        std::cout << "Некорректный ввод. Пожалуйста, выберите от 1 до 3.\n";
    }
}

int main()
{
    system("cls");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // // Создаем экземпляр базы данных
    // Database db("UniversityDB");

    // // Добавляем таблицу "Group"
    // db.addTable("Group");
    // Table &groupTable = db.getTable("Group");

    // // Добавляем поля в таблицу "Group"
    // groupTable.addField("Id", Field::INTEGER, 100, true, true);
    // groupTable.addField("GroupName", Field::VARCHAR, 50, false, true);

    // // Добавляем таблицу "Student"
    // db.addTable("Student");
    // Table &studentTable = db.getTable("Student");

    // // Добавляем поля в таблицу "Student"
    // studentTable.addField("Id", Field::INTEGER, 100, true, true);
    // studentTable.addField("FirstName", Field::VARCHAR, 50, false, true);
    // studentTable.addField("LastName", Field::VARCHAR, 50, false, true);
    // studentTable.addField("Group_id", Field::INTEGER, 100, true, true);

    // // Добавляем внешний ключ в таблицу "Student", связывающий ее с таблицей "Group"
    // studentTable.addForeignKey("Group_id", "Group", "Id");

    // // Добавляем записи в таблицу "Group"
    // db.addRecordToTable("Group", {{"Id", "1"}, {"GroupName", "Group A"}});
    // db.addRecordToTable("Group", {{"Id", "2"}, {"GroupName", "Group B"}});

    // // Добавляем записи в таблицу "Student"
    // db.addRecordToTable("Student", {{"Id", "1"}, {"FirstName", "John"}, {"LastName", "Doe"}, {"Group_id", "1"}});
    // db.addRecordToTable("Student", {{"Id", "2"}, {"FirstName", "Alice"}, {"LastName", "Smith"}, {"Group_id", "2"}});

    // // Выводим содержимое базы данных
    // db.printDatebaseValue();
    bool exitProgram = false;
    bool *prtExit = &exitProgram;
    while (!exitProgram)
    {
        showMainMenu(prtExit);
    }

    system("cls");
    return 0;
}
