#include "Person.h"

Person::Person(string name, unsigned int age, unsigned int phone,
		string email) {
	this->name = name;
	this->age = age;
	this->phone = phone;
	this->email = email;
}

Person::Person(ifstream& s) {
	stringstream ss;
	string name, email, sAge, sPhone;
	unsigned int age, phone;

	getline(s, name, ';');
	this->name = name;

	getline(s, sAge, ';');
	ss << sAge;
	ss >> age;
	ss.clear();
	this->age = age;

	getline(s, sPhone, ';');
	ss << sPhone;
	ss >> phone;
	ss.clear();
	this->phone = phone;

	getline(s, email, ';');
	this->email = email;
}

void Person::saveData(ofstream &of) {
	of << name << ";" << age << ";" << phone << ";" << email << ";";
}

Person::~Person() {
}

void Person::setName(string name) {
	this->name = name;
}

vector<Employee *> Person::getEmployeeTeam() const {
	vector<Employee *> v;
	return v;
}

string Person::getName() const {
	return name;
}

void Person::setAge(unsigned int age) {
	this->age = age;
}

unsigned int Person::getAge() const {
	return age;
}

void Person::setPhone(unsigned int phone) {
	this->phone = phone;
}

unsigned int Person::getPhone() const {
	return phone;
}

void Person::setEmail(string email) {
	this->email = email;
}

string Person::getEmail() const {
	return email;
}

string Person::print() const {
	stringstream ss;
	ss << name.substr(0, 22);

	if (name.size() >= 23)
		ss << "\t";
	else
		for (int i = 23 - name.size(); i > 0; i -= 8)
			ss << "\t";

	ss << age << "\t" << phone << "\t" << email.substr(0, 22);
	return ss.str();
}

