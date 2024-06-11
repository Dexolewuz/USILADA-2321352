#include <iostream>
#include <vector>
#include "general.h"
#ifndef GESTION_DATA_H
#define GESTION_DATA_H

bool comparePersons(const Person &a, const Person &b);
bool binarySearch(const std::vector<Person> &persons, int dni, Person &result);
std::vector<Person> getPersons();
Person getPersonByDni(int dni, std::vector<Person> &data);
#endif