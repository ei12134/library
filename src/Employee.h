/*
 * Employee.h
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "Person.h"
using namespace std;

class Employee: public Person{
	unsigned long nif;
	unsigned int wage;
public:
	Employee(string name,int age,unsigned long phoneNumber,string email,unsigned long nif,unsigned int wage);
	virtual ~Employee();
	unsigned long getNif()const;
	void setNif(unsigned long nif);
	unsigned int getWage()const;
	void setWage(unsigned int wage);
	//void createBorrow(Book *,Reader *,Employee *);
	string printInfo();
};
#endif /* EMPLOYEE_H_ */


