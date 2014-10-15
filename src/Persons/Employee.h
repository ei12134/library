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
public:
	Employee(fstream& s);
	Employee(string name, unsigned int age, unsigned int phone, string email,
			unsigned int nif, unsigned int wage);
	virtual ~Employee();
	unsigned int getNif() const;
	unsigned int getWage() const;
	void setNif(unsigned int nif);
	void setWage(unsigned int wage);
	void createBorrow(Book *, Reader *, Employee *);
	string print();
	unsigned int getType();
};
#endif /* EMPLOYEE_H_ */

