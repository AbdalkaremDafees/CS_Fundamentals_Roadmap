/*
            Poject 2: Separate Classes In Libraries 
               To Organizing Code Using Libraries
*/

#include <iostream>
#include "clsPerson.h"
#include "clsEmployee.h"
#include "clsDeveloper.h"
using namespace std;

int main()
{
    clsDeveloper Developer1(10, "EmployeeFirst", "EmployeeLast", "a@a.com", "0968686868", "AI Engineer", "IT Department", 9000, "Python");

    Developer1.Print();

    system("pause>0");
    return 0;
}