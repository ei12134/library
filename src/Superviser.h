/*
 * Superviser.h
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "Employee.h"

using namespace std;

class Superviser: public Employee{
	vector<Employee *> teamvec;
public:
	Superviser(string name,int age,unsigned long phoneNumber,string email,unsigned long nif,unsigned int wage );
	virtual ~Superviser();
	void addEmployee(Employee *e1);
	bool removeEmployee(string name);
	string printInfo();


};


