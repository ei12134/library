/*
 * Superviser.cpp
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */

#include "Superviser.h"

using namespace std;

Superviser::Superviser(string name, int age, unsigned long phoneNumber,
		string email, unsigned long nif, unsigned int wage) :
		Employee(name, age, phoneNumber, email, nif, wage) {

}
Superviser::~Superviser() {
}

void Superviser::addEmployee(Employee *e1) {
	teamvec.push_back(e1);
}

bool Superviser::removeEmployee(string name) {
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
string Superviser::printInfo() {
	stringstream ss;
	for (vector<Employee *>::iterator it = teamvec.begin(); it != teamvec.end();
			it++) {
		ss << (*it)->printInfo() << "\n";
	}
	return ss.str();
}

