#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "Employee.h"

using namespace std;

class Supervisor: public Employee {
	vector<Employee *> teamvec;
public:
	Supervisor(string name, int age, unsigned long int phone, string email,
			unsigned long int nif, unsigned long int wage);
	virtual ~Supervisor();
	void addEmployee(Employee *e1);
	bool removeEmployee(string name);
	string print();

};

