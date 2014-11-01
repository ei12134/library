#include "Supervisor.h"

using namespace std;

Supervisor::Supervisor(string name, int age, unsigned int phoneNumber,
		string email, unsigned int nif, unsigned int wage) :
		Employee(name, age, phoneNumber, email, nif, wage) {
}

Supervisor::Supervisor(fstream& s) :
		Employee(s) {
}

Supervisor::~Supervisor() {
}

void Supervisor::addEmployee(Employee *e1) {
	team.push_back(e1);
}

vector<Borrow*> Supervisor::getBorrowedBooks() const {
	vector<Borrow*> empty;
	return empty;
}

bool Supervisor::removeEmployee(string name) {
	for (vector<Employee *>::iterator it = team.begin(); it != team.end();
			it++) {
		if ((*it)->getName() == name) {
			team.erase(it);
			return true;
		}
	}
	return false;
}

string Supervisor::print() {
	return Employee::print();
}

unsigned int Supervisor::getType() {
	return 3;
}

unsigned int Supervisor::getCard() const {
	return 0;
}

string Supervisor::printType() {
	return "Supervisor";
}
