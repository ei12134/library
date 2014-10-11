/*
 * Employee.cpp
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */
#include "Employee.h"

using namespace std;

Employee::Employee(string name, unsigned int age, unsigned long int phoneNumber,
		string email, unsigned long int nif, unsigned long int wage) :
		Person(name, age, phoneNumber, email) {
	this->nif = nif;
	this->wage = wage;
}

Employee::~Employee() {
}

unsigned long int Employee::getNif() const {
	return nif;
}

void Employee::setNif(unsigned long int nif) {
	this->nif = nif;
}
unsigned long int Employee::getWage() const {
	return wage;
}
void Employee::setWage(unsigned long int wage) {
	this->wage = wage;
}

//void createBorrow(Book *, Reader *, Employee *);

string Employee::print() {
	stringstream ss;
	ss << Person::print() << " ; " << nif << " ; " << wage;
	return ss.str();
}

