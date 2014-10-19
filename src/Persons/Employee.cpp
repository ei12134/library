#include "Employee.h"

Employee::Employee(string name, unsigned int age, unsigned int phoneNumber,
		string email, unsigned int nif, unsigned int wage) :
		Person(name, age, phoneNumber, email) {
	this->nif = nif;
	this->wage = wage;
}

Employee::Employee(fstream& s) :
		Person(s) {
	stringstream ss;
	string sNif, sWage;
	unsigned int nif, wage;

	getline(s, sNif, ';');
	ss << sNif;
	ss >> nif;
	ss.clear();
	this->nif = nif;

	getline(s, sWage); // read last input until newline
	ss << sWage;
	ss >> wage;
	ss.clear();
	this->wage = wage;
}

Employee::~Employee() {
}

unsigned int Employee::getNif() const {
	return nif;
}

void Employee::setNif(unsigned int nif) {
	this->nif = nif;
}
unsigned int Employee::getWage() const {
	return wage;
}
void Employee::setWage(unsigned int wage) {
	this->wage = wage;
}

void createBorrow(Book *, Reader *, Employee *) {
}

string Employee::print() {
	stringstream ss;
	ss << Person::print() << "   " << nif << "   " << wage;
	return ss.str();
}

unsigned int Employee::getType() {
	return 2;
}

unsigned int Employee::getCard() const {
	return 0;
}

