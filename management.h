
#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <vector>
#include "init.h"
#include "database.h"
#include "general.h"

namespace management_cpp
{
  class Management
  {
  public:
    Management();
    ~Management();

    static void prepareData(std::vector<std::vector<Person>> &personsList);
    static Person findByDNI(std::vector<std::vector<Person>> &personsList, const int &dni);
/*static bool updateRecord(const int &dni, const Person &updatedPerson);*/
  };

  void Management::prepareData(std::vector<std::vector<Person>> &personsList)
  {
    try
    {
      init::ConfigRead configRead;
      configRead.Open("config.ini");
      std::string filename = configRead.GetValue("Database", "filename");
      int sizeOfBlock = std::stoi(configRead.GetValue("Order", "sizeOfBlock"));
      configRead.Close();
      database_cpp::Database::readPersons(filename, personsList, sizeOfBlock);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  Person Management::findByDNI(std::vector<std::vector<Person>> &personsList, const int &dni)
  {
    try
    {
      Person person;
      for (const auto &personList : personsList)
      {
        if (binarySearch(personList, dni, person))
        {
          return person;
        }
      }
      return person;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return Person();
    }
  }
/*
ACTUALIZAR REGISTRO
  bool Management::updateRecord(const int &dni, const Person &updatedPerson)
  {
    try
    {
      std::vector<std::vector<Person>> personsList;
      prepareData(personsList);

      bool updated = false;
      for (auto &personList : personsList)
      {
        for (auto &person : personList)
        {
          if (person.dni == dni)
          {
            person = updatedPerson;
            updated = true;
            break;
          }
        }
        if (updated) break;
      }

      if (!updated)
      {
        std::cerr << "Record not found for DNI: " << dni << std::endl;
        return false;
      }

      init::ConfigRead configRead;
      configRead.Open("config.ini");
      std::string filename = configRead.GetValue("Database", "filename");
      configRead.Close();

      std::ofstream outFile(filename, std::ios::binary);
      for (const auto &personList : personsList)
      {
        for (const auto &person : personList)
        {
          database_cpp::Database::writePerson(person, outFile);
        }
      }
      outFile.close();

      return true;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      return false;
    }
  }*/
}

#endif
