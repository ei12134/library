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
	Supervisor(string name, int age, unsigned int phone, string email,
			unsigned int nif, unsigned int wage);
	Supervisor(fstream& s);
	virtual ~Supervisor();
	void addEmployee(Employee *e1);
	bool removeEmployee(string name);
	string print();
};

