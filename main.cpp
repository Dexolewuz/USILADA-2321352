#include <iostream>
#include <vector>
#include "general.h"
#include "generate.data.h"
#include "gestion.data.h"
#include "colors.h"

using namespace std;

vector<Person> persons;

int main()
{

  cout << endl;
  cout << BLACK << BG_GREEN << "*************** Sistema de Registro Nacional ***************" << RESET << endl;
  cout << endl;
  cout << GREEN << "============================" << RESET << endl;
  cout << GREEN << "Seleccione la opcion deseada" << RESET << endl;
  cout << GREEN << "============================" << RESET << endl;
  cout << YELLOW << "[1] Generar datos de prueba" << RESET << endl;
  cout << YELLOW << "[2] Gestionar registro" << RESET << endl;
  cout << RED << "[3] Salir" << RESET << endl;
  cout << GREEN << "============================" << RESET << endl;
  int option;
  cout << "Opcion: ";
  cin >> option;
  cout << GREEN << "============================" << RESET << endl;
  if (option == 1)
  {
    cout << GREEN << "============================" << RESET << endl;
    cout << GREEN << "Ingrese la cantidad de registros a generar" << RESET << endl;
    cout << GREEN << "============================" << RESET << endl;
    cout << "Cantidad: ";
    int totalRecords;
    cin >> totalRecords;
    cout << GREEN << "============================" << RESET << endl;
    cout << "Generando..." << endl;
    generateData(totalRecords);
  }
  else if (option == 2)
  {
    cout << "Cargando..." << endl;
    persons = getPersons();
    cout << GREEN << "============================" << RESET << endl;
    cout << GREEN << "Seleccione una operacion" << RESET << endl;
    cout << GREEN << "============================" << RESET << endl;
    cout << YELLOW << "[1] Buscar por DNI" << RESET << endl;
    cout << GREEN << "============================" << RESET << endl;
    cout << "Opcion: ";
    cin >> option;
    cout << GREEN << "============================" << RESET << endl;
    if (option == 1)
    {
      int dni;
      cout << "DNI: ";
      cin >> dni;
      Person person = getPersonByDni(dni, persons);
    }
  }
  else if (option == 3)
  {
    cout << GREEN << "Gracias por usar el sistema" << RESET << endl;
    cout << endl;
    exit(0);
  }
  return 0;
}