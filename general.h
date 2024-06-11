#include <iostream>

#ifndef GENERAL_DATA_H
#define GENERAL_DATA_H

struct Address
{
  std::string department;
  std::string province;
  std::string district;
  std::string city;
};

struct Person
{
  int dni;
  std::string name;
  std::string lastName;
  std::string nationality;
  Address address;
  std::string phoneNumber;
  std::string email;
  std::string civilStatus;
};

#endif