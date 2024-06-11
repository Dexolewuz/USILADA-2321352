#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include <sstream>
#include <random>
#include "generate.data.h"

using namespace std;
using namespace chrono;

vector<string> names;
vector<string> last_names;
vector<string> last_names_2;
vector<string> nationalities = {"Peru"};
vector<string> departments = {"Lima"};
vector<string> provinces = {"Lima"};
vector<string> districts = {"Ate", "La Victoria"};
vector<string> cities = {"City1", "City2"};
vector<string> civil_statuses = {"Single", "Married"};

mutex fileMutex;

string getRandomString(const vector<string> &list)
{
  int index = rand() % list.size();
  return list[index];
}

string getRandomEmail(string name)
{
  return name + "@example.com";
}

string generateRecord(int id)
{
  string _id = to_string(10000000 + id);
  string name = getRandomString(names);
  string lastName1 = getRandomString(last_names);
  string lastName2 = getRandomString(last_names);
  string last_name = lastName1 + " " + lastName2;
  string nationality = getRandomString(nationalities);
  string department = getRandomString(departments);
  string province = getRandomString(provinces);
  string district = getRandomString(districts);
  string city = getRandomString(cities);
  string phoneNumber = "12345678";
  string email = getRandomEmail("example_" + _id);
  string civilStatus = getRandomString(civil_statuses);
  return _id + "," + name + " " + last_name + "," + nationality + "," + department + "," + province + "," + district + "," + city + "," + phoneNumber + "," + email + "," + civilStatus + "\n";
}

void writeBlock(const string &filename, int start, int end)
{
  string buffer;
  buffer.reserve((end - start) * 30); // Reserva memoria para reducir las realocaciones
  // buffer += "dni,name,nationality,department,province,district,city,phone_number,email,civil_status\n";
  for (int i = start; i < end; ++i)
  {
    buffer += generateRecord(i);
  }

  // Bloqueo de mutex antes de escribir en el archivo
  lock_guard<mutex> guard(fileMutex);
  ofstream outfile(filename, ios::out | ios::app);
  outfile << buffer;
}

// Función principal para generar el archivo CSV con multihilo y futuros
void generateCSV(const string &filename, int totalRecords, int blockSize, int numThreads)
{
  // Crear o truncar el archivo antes de empezar
  ofstream outfile(filename, ios::out | ios::trunc);
  outfile.close();

  vector<future<void>> futures;

  for (int i = 0; i < totalRecords; i += blockSize * numThreads)
  {
    for (int j = 0; j < numThreads; ++j)
    {
      int start = i + j * blockSize;
      int end = min(start + blockSize, totalRecords);
      if (start < totalRecords)
      {
        futures.push_back(async(launch::async, writeBlock, filename, start, end));
      }
    }
    if (i % 1000000 == 0)
    {
      cout << "Progreso: " << (i / 1000000) << " millones de registros generados.\n";
    }
    // Espera a que todos los hilos terminen antes de continuar
    for (auto &f : futures)
    {
      f.get();
    }
    futures.clear();
  }
}

void generateData(int totalRecords)
{
  const string filename = "output1.csv";
  const int blockSize = 100000;
  const int numThreads = 4;

  ifstream fin("test.csv");

  if (!fin.is_open())
  {
    cerr << "Error: No se pudo abrir el archivo." << endl;
  }

  string line;

  while (getline(fin, line))
  {
    stringstream ss(line);
    string word;

    getline(ss, word, ',');
    names.push_back(word);
    getline(ss, word, ',');
    last_names.push_back(word);
    getline(ss, word, ',');
    last_names_2.push_back(word);
  }

  cout << endl;

  fin.close();

  auto start = high_resolution_clock::now();
  cout << "Proceso iniciado" << endl;
  generateCSV(filename, totalRecords, blockSize, numThreads);

  auto end = high_resolution_clock::now();
  duration<double> elapsed = end - start;
  cout << "CSV generated in " << elapsed.count() << " seconds." << endl;
}
