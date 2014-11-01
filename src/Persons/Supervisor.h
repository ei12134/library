#ifndef SUPERVISOR_H_
#define SUPERVISOR_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "Employee.h"
using namespace std;

class Supervisor: public Employee {
	vector<Employee *> team;
public:
	Supervisor(string name, int age, unsigned int phone, string email,
			unsigned int nif, unsigned int wage);
	Supervisor(fstream& s);
	virtual ~Supervisor();
	void addEmployee(Employee *e1);
	bool removeEmployee(string name);
	vector<Borrow*> getBorrowedBooks() const;
	string print();
	unsigned int getType();
	unsigned int getCard() const;
	string printType();
};

#endif /* SUPERVISOR_H_ */
