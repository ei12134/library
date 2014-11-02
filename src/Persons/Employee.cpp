#include "Employee.h"

Employee::Employee(string name, unsigned int age, unsigned int phoneNumber,
		string email, unsigned int nif, unsigned int wage, bool supervisor) :
		Person(name, age, phoneNumber, email) {
	this->nif = nif;
	this->wage = wage;
	this->supervisor = supervisor;
}

Employee::Employee(fstream& s) :
		Person(s) {
	stringstream ss;
	string sNif, sWage, sSupervisor;
	unsigned int nif, wage;
	bool supervisor;

	getline(s, sNif, ';');
	ss << sNif;
	ss >> nif;
	ss.clear();
	this->nif = nif;

	getline(s, sWage, ';');
	ss << sWage;
	ss >> wage;
	ss.clear();
	this->wage = wage;

	getline(s, sSupervisor); // read last input until newline
	ss << sSupervisor;
	ss >> supervisor;
	ss.clear();
	this->supervisor = supervisor;
}

Employee::~Employee() {
}

vector<Borrow*> Employee::getBorrowedBooks() const {
	vector<Borrow*> empty;
	return empty;
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
	if (!supervisor)
		return 2;
	else
		return 3;
}

void Employee::setSupervisor(bool super) {
	this->supervisor = super;
}

bool Employee::isSupervisor() const {
	return supervisor;
}

unsigned int Employee::getCard() const {
	return 0;
}

string Employee::printType() {
	if (!supervisor)
		return "[Employee]";
	else
		return "[Supervisor]";
}
