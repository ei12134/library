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
	teamvec.push_back(e1);
}

bool Supervisor::removeEmployee(string name) {
	for (vector<Employee *>::iterator it = teamvec.begin(); it != teamvec.end();
			it++) {
		if ((*it)->getName() == name) {
			teamvec.erase(it);
			return true;
		}
		return false;
	}
	return false;

}

string Supervisor::print() {
	return Employee::print();
}

