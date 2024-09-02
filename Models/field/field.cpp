#include "field.h"

Field::Field(std::string _namefield, VALUE_type _val, int _sizeField, bool _primaryKeyField, bool _notNullField)
    : nameField(_namefield),
      val(_val),
      sizeField(_sizeField),
      primaryKeyField(_primaryKeyField),
      notNullField(_notNullField){};

Field::Field(const std::string &serializedData)
{
  std::istringstream ss(serializedData);
  std::string token;

  
  std::getline(ss, token, ':');
  nameField = token;

  std::getline(ss, token, ':');
  val = static_cast<VALUE_type>(std::stoi(token) - 1);

  std::getline(ss, token, ':');
  sizeField = std::stoi(token);

  std::getline(ss, token, ':');
  primaryKeyField = std::stoi(token);

  std::getline(ss, token, ':');
  notNullField = (token == "1");
}

std::string Field::getNameField() const
{
  return nameField;
}

Field::VALUE_type Field::getType() const
{
  return val;
}

int Field::getSizeField()
{
  return sizeField;
}

bool Field::isPrimaryKey()
{
  return primaryKeyField;
}

bool Field::isNotNull()
{
  return notNullField;
}

void Field::setNameField(const std::string &nameField)
{
  this->nameField = nameField;
}

void Field::setType(VALUE_type val)
{
  this->val = val;
}

void Field::setSizeField(int sizeField)
{
  this->sizeField = sizeField;
}

void Field::setPrimaryKey(bool primaryKeyField)
{
  this->primaryKeyField = primaryKeyField;
}

void Field::setNotNull(bool notNullField)
{
  this->notNullField = notNullField;
}

std::string Field::getFieldName() const
{
  return nameField;
}

void Field::printField()
{
  std::string typeStr;
  switch (val)
  {
  case INTEGER:
    typeStr = "INTEGER";
    break;
  case DATETIME:
    typeStr = "DATETIME";
    break;
  case VARCHAR:
    typeStr = "VARCHAR";
    break;
  case BIT:
    typeStr = "BIT";
    break;
  default:
    typeStr = "UNKNOWN";
    break;
  }
  std::cout << "Name: " << nameField << " Type: " << typeStr << " (" << sizeField << ") PrimaryKey: " << primaryKeyField << " NotNull: " << notNullField << std::endl;
}

void Field::setTypeValue(VALUE_type val)
{
  values.clear();
  switch (val)
  {
  case INTEGER:
    values.push_back(std::make_shared<Int>());
    break;
  case DATETIME:
    values.push_back(std::make_shared<DateTime>());
    break;
  case VARCHAR:
    values.push_back(std::make_shared<Varchar>());
    break;
  case BIT:
    values.push_back(std::make_shared<Bit>());
    break;
  }
}

void Field::addValue(int value)
{

  values.push_back(std::make_shared<Int>(sizeField, value));
}

void Field::addValue(std::string value)
{
  switch (val)
  {
  case DATETIME:
    values.push_back(std::make_shared<Varchar>(sizeField, value));
    break;
  case VARCHAR:
    values.push_back(std::make_shared<Varchar>(sizeField, value));
    break;
  }
}

void Field::addValue(bool value)
{
  values.push_back(std::make_shared<Bit>(sizeField, value));
}

void Field::setValue(const std::string &value)
{

  switch (val)
  {
  case INTEGER:
  {

    int intValue = std::stoi(value);

    addValue(intValue);
    break;
  }
  case DATETIME:
  {

    addValue(value);
    break;
  }
  case VARCHAR:
  {

    addValue(value);
    break;
  }
  case BIT:
  {

    bool bitValue = (value == "true" || value == "1");

    addValue(bitValue);
    break;
  }
  default:
  {
    std::cerr << "Ошибка: Неизвестный тип поля." << std::endl;
    break;
  }
  }
}

void Field::saveToFile(std::ofstream &file)
{
  int typeStr = 0;
  switch (val)
  {
  case INTEGER:
    typeStr = 1;
    break;
  case DATETIME:
    typeStr = 2;
    break;
  case VARCHAR:
    typeStr = 3;
    break;
  case BIT:
    typeStr = 4;
    break;
  default:
    typeStr = 0;
    break;
  }

  std::string serializedData = nameField + ":" + std::to_string(typeStr) + ":" + std::to_string(sizeField) + ":" + std::to_string(primaryKeyField) + ":" + (notNullField ? "1" : "0");
  file << serializedData << std::endl;
}

void Field::loadFromFile(std::ifstream &file)
{
  if (!file.is_open())
  {
    // Handle file not open error
    std::cout<<"NHf,"<<std::endl;
    return;
  }

  std::string serializedData;
  std::getline(file, serializedData);
  *this = Field(serializedData);
}