#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "../Book.h"
#include "Person.h"
#include "Reader.h"
using namespace std;

class Employee: public Person {
	unsigned int nif, wage;
	bool supervisor;
	vector<Employee *> team;
public:
	Employee(stringstream& s, bool superv);
	Employee(string name, unsigned int age, unsigned int phone, string email,
			unsigned int nif, unsigned int wage, bool supervisor);
	virtual ~Employee();

	void saveData(ofstream &of);
	unsigned int getNif() const;
	unsigned int getWage() const;
	unsigned int getType() const;
	unsigned int getCard() const;
	vector<Employee *> getEmployeeTeam() const;
	void setSupervisor(bool super);
	bool getSupervisor() const {
		return supervisor;
	}
	void addEmployee(Employee * e);
	bool removeEmployee(Employee * e);
	void clearEmployeesTeam();

	bool getInactive() const {
		return false;
	}
	void setInactive(bool Inactive) {
	}

	void setNif(unsigned int nif);
	void setWage(unsigned int wage);
	vector<Borrow*> getBorrowedBooks() const;
	bool addBorrow(Borrow* borrow);
	string print() const;
	string printType() const;
};
#endif /* EMPLOYEE_H_ */
