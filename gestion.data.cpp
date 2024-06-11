#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include "gestion.data.h"
#include "rapidcsv.h"
#include <cstring>
using namespace std;
using namespace chrono;

bool comparePersons(const Person &p1, const Person &p2)
{
  return p1.dni < p2.dni;
}

bool binarySearch(const vector<Person> &persons, int dni, Person &result)
{
  int left = 0;
  int right = persons.size() - 1;

  while (left <= right)
  {
    int mid = left + (right - left) / 2;
    if (persons[mid].dni == dni)
    {
      result = persons[mid];
      return true;
    }
    if (persons[mid].dni < dni)
    {
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }

  return false;
}

struct Node
{
  vector<string> data;
  struct Node *next;
};

int getBucketIndex(int value, int interval)
{
  return value / interval;
}
// =============================== Quick Sort ===============================
int partition(vector<Person> &data, int low, int high)
{
  int pivot = data[high].dni;
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++)
  {
    if (data[j].dni < pivot)
    {
      i++;
      std::swap(data[i], data[j]);
    }
  }
  std::swap(data[i + 1], data[high]);
  return (i + 1);
}

void quickSort(vector<Person> &data, int low, int high)
{
  if (low < high)
  {
    int pi = partition(data, low, high);

    quickSort(data, low, pi - 1);
    quickSort(data, pi + 1, high);
  }
}

// =============================== QuicK Sort ===============================
// =============================== Counting Sort =============================
vector<Person> countSort(vector<Person> &data)
{
  int size = data.size();
  int _max = 0;
  for (int i = 0; i < size; i++)
  {
    _max = max(_max, data[i].dni);
  }
  vector<int> countArray(_max + 1, 0);
  for (int i = 0; i < size; i++)
  {
    countArray[data[i].dni]++;
  }
  for (int i = 1; i <= _max; i++)
  {
    countArray[i] += countArray[i - 1];
  }
  vector<Person> outputArray(size);
  for (int i = size - 1; i >= 0; i--)
  {
    outputArray[countArray[data[i].dni] - 1] = data[i];
    countArray[data[i].dni]--;
  }
  return outputArray;
}
// =============================== Counting Sort =============================
// =============================== Heap Sort =============================
void heapify(vector<Person> &data, int size, int i)
{
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < size && data[l].dni > data[largest].dni)
    largest = l;

  if (r < size && data[r].dni > data[largest].dni)
    largest = r;

  if (largest != i)
  {
    std::swap(data[i], data[largest]);
    heapify(data, size, largest);
  }
}

void heapSort(vector<Person> &data, int size)
{
  for (int i = size / 2 - 1; i >= 0; --i)
  {
    heapify(data, size, i);
  }

  for (int i = size - 1; i > 0; --i)
  {
    std::swap(data[0], data[i]);
    heapify(data, i, 0);
  }
}
// =============================== Heap Sort =============================
// =============================== Insertion Sort =============================
void insertionSort(vector<Person> &data, int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = data[i].dni;
    j = i - 1;
    while (j >= 0 && data[j].dni > key)
    {
      data[j + 1].dni = data[j].dni;
      j = j - 1;
    }
    data[j + 1].dni = key;
  }
}
// =============================== Insertion Sort =============================
// =============================== Selection Sort =============================
void selectionSort(vector<Person> &data, int n)
{
  int i, j, min_idx;
  for (i = 0; i < n - 1; i++)
  {
    min_idx = i;
    for (j = i + 1; j < n; j++)
    {
      if (data[j].dni < data[min_idx].dni)
      {
        min_idx = j;
      }
    }

    if (min_idx != i)
    {
      std::swap(data[min_idx], data[i]);
    }
  }
}
// =============================== Selection Sort =============================
// =============================== Radix Sort =============================
// int getMax(vector<Person> data, int n)
// {
//   int max = data[0].dni;
//   for (int i = 1; i < n; i++)
//   {
//     if (data[i].dni > max)
//     {
//       max = data[i].dni;
//     }
//   }
//   return max;
// }
// void countSort1(vector<Person> &data, int n, int exp)
// {
//   int count[10] = {0};
//   for (int i = 0; i < n; i++)
//   {
//     count[(data[i].dni / exp) % 10]++;
//   }
//   for (int i = 1; i < 10; i++)
//   {
//     count[i] += count[i - 1];
//   }
//   vector<Person> output(n);
//   for (int i = n - 1; i >= 0; i--)
//   {
//     output[count[(data[i].dni / exp) % 10] - 1] = data[i];
//     count[(data[i].dni / exp) % 10]--;
//   }
//   data = std::move(output);
// }
// void radixSort(vector<Person> &data, int n)
// {
//   int m = getMax(data, n);
//   for (int exp = 1; m / exp > 0; exp *= 10)
//   {
//     countSort1(data, n, exp);
//   }
// }
// Función de Counting Sort para ordenar según el dígito especificado
void countingSort1(vector<Person> &data, int exp)
{
  int size = data.size();
  vector<Person> output(size);
  int count[10] = {0};

  // Contar ocurrencias de los dígitos
  for (int i = 0; i < size; i++)
  {
    int digit = (data[i].dni / exp) % 10;
    count[digit]++;
  }

  // Cambiar count[i] para contener la posición real de este dígito en output[]
  for (int i = 1; i < 10; i++)
  {
    count[i] += count[i - 1];
  }

  // Construir el output array
  for (int i = size - 1; i >= 0; i--)
  {
    int digit = (data[i].dni / exp) % 10;
    output[count[digit] - 1] = data[i];
    count[digit]--;
  }

  // Copiar el output array a data[], para que data[] contenga los elementos ordenados según el dígito actual
  for (int i = 0; i < size; i++)
  {
    data[i] = output[i];
  }
}

// Función principal de Radix Sort
vector<Person> radixSort(vector<Person> &data)
{
  // Encontrar el máximo número para saber el número de dígitos
  int maxDni = 0;
  for (const Person &person : data)
  {
    maxDni = max(maxDni, person.dni);
  }

  // Aplicar Counting Sort a cada dígito
  for (int exp = 1; maxDni / exp > 0; exp *= 10)
  {
    countingSort1(data, exp);
  }

  return data;
}
// =============================== Radix Sort =============================
// =============================== Hybrid Sort =============================
const int HEAPSORT_THRESHOLD = 100; // Tamaño de sublistas para cambiar a HeapSort

void heapify1(vector<Person> &data, int n, int i)
{
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && data[left].dni > data[largest].dni)
    largest = left;

  if (right < n && data[right].dni > data[largest].dni)
    largest = right;

  if (largest != i)
  {
    swap(data[i], data[largest]);
    heapify1(data, n, largest);
  }
}

void heapSort1(vector<Person> &data, int left, int right)
{
  int n = right - left + 1;
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify1(data, left + n, left + i);

  for (int i = n - 1; i > 0; i--)
  {
    swap(data[left], data[left + i]);
    heapify1(data, left + i, left);
  }
}

int partition1(vector<Person> &data, int left, int right)
{
  int pivot = data[right].dni;
  int i = left - 1;
  for (int j = left; j < right; j++)
  {
    if (data[j].dni <= pivot)
    {
      i++;
      swap(data[i], data[j]);
    }
  }
  swap(data[i + 1], data[right]);
  return i + 1;
}

void quickSort1(vector<Person> &data, int left, int right)
{
  if (left < right)
  {
    if (right - left < HEAPSORT_THRESHOLD)
    {
      heapSort1(data, left, right);
    }
    else
    {
      int pivot = partition1(data, left, right);
      quickSort1(data, left, pivot - 1);
      quickSort1(data, pivot + 1, right);
    }
  }
}

vector<Person> hybridSort(vector<Person> &data)
{
  quickSort(data, 0, data.size() - 1);
  return data;
}
//  =============================== Hybrid Sort =============================

vector<vector<string>> linkedListToVector(struct Node *head)
{
  vector<vector<string>> result;
  while (head != NULL)
  {
    result.push_back(head->data);
    head = head->next;
  }
  return result;
}

vector<Person> getPersons()
{

  fstream file;
  file.open("output1.csv", ios::in);
  if (!file.is_open())
  {
    cerr << "Error: No se pudo abrir el archivo." << endl;
  }

  // auto start = high_resolution_clock::now();
  // cout << "Proceso iniciado" << endl;
  vector<Person> persons;
  string line, word;

  getline(file, line);
  while (getline(file, line))
  {
    stringstream ss(line);
    Person person;
    getline(ss, word, ',');
    person.dni = stoi(word);
    getline(ss, word, ',');
    person.name = word;
    getline(ss, word, ',');
    person.nationality = word;
    getline(ss, word, ',');
    person.address.department = word;
    getline(ss, word, ',');
    person.address.province = word;
    getline(ss, word, ',');
    person.address.district = word;
    getline(ss, word, ',');
    person.address.city = word;
    getline(ss, word, ',');
    person.phoneNumber = word;
    getline(ss, word, ',');
    person.email = word;
    getline(ss, word, ',');
    person.civilStatus = word;
    persons.push_back(person);
  }

  file.close();

  // auto end = high_resolution_clock::now();
  // duration<double> elapsed = end - start;
  // cout << "CSV readed in " << elapsed.count() << " seconds." << endl;

  // start = high_resolution_clock::now();
  // cout << "Proceso iniciado" << endl;
  heapSort(persons, persons.size());
  // end = high_resolution_clock::now();
  // elapsed = end - start;
  // cout << "CSV sorted in " << elapsed.count() << " seconds." << endl;

  return persons;
}

void bucketSort(vector<vector<string>> &data)
{
  int size = data.size();
  int limit_items_per_bucket = 1000000;
  int n_buckets = (size + limit_items_per_bucket - 1) / limit_items_per_bucket; // Ensure to cover all elements
  struct Node **buckets = (struct Node **)malloc(n_buckets * sizeof(struct Node *));

  for (int i = 0; i < n_buckets; i++)
  {
    buckets[i] = NULL;
  }

  for (int i = 0; i < size; ++i)
  {
    struct Node *current;
    int pos = getBucketIndex(stoi(data[i][0]), limit_items_per_bucket);
    current = (struct Node *)malloc(sizeof(struct Node));
    current->data = data[i];
    current->next = buckets[pos];
    buckets[pos] = current;
  }

  data.clear();

  for (int i = 0; i < n_buckets; ++i)
  {
    if (buckets[i] != NULL)
    {
      vector<vector<string>> bucketVector = linkedListToVector(buckets[i]);
      // heapSort(bucketVector, bucketVector.size());
      for (const auto &entry : bucketVector)
      {
        data.push_back(entry);
      }
    }
  }
  free(buckets);
}

Person getPersonByDni(int dni, vector<Person> &data)
{

  auto start = high_resolution_clock::now();
  cout << "Proceso iniciado" << endl;
  Person result;
  bool found = binarySearch(data, dni, result);
  auto end = high_resolution_clock::now();
  duration<double> elapsed = end - start;
  cout << "Found in " << elapsed.count() << " seconds." << endl;

  if (found)
  {
    std::cout << "Registro encontrado:\n";
    std::cout << "DNI: " << result.dni << "\n";
    std::cout << "Nombre: " << result.name << "\n";
    std::cout << "Nacionalidad: " << result.nationality << "\n";
    std::cout << "Dirección: " << result.address.department << ", "
              << result.address.province << ", "
              << result.address.district << ", "
              << result.address.city << "\n";
    std::cout << "Teléfono: " << result.phoneNumber << "\n";
    std::cout << "Email: " << result.email << "\n";
    std::cout << "Estado Civil: " << result.civilStatus << "\n";
    return result;
  }
  else
  {
    return Person();
  }
}