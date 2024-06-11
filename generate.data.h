#include <iostream>
#include <vector>

#ifndef GENERATE_DATA_H
#define GENERATE_DATA_H

std::string getRandomString(const std::vector<std::string> &list);
std::string getRandomEmail(std::string name);
std::string generateRecord(int id);
void writeBlock(const std::string &filename, int start, int end);
void generateCSV(const std::string &filename, int totalRecords, int blockSize, int numThreads);
void generateData(int totalRecords);
#endif