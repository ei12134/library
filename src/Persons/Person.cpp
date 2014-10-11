/*
 * Person.cpp
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */
#include "Person.h"

using namespace std;

Person::Person(string name, unsigned int age, unsigned long phoneNumber,
		string email) {
	this->name = name;
	this->age = age;
	this->phoneNumber = phoneNumber;
	this->email = email;
}

Person::~Person() {

}

void Person::setName(string name) {
	this->name = name;
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

void Person::setPhoneNumber(unsigned long phoneNumber) {
	this->phoneNumber = phoneNumber;
}

unsigned long Person::getPhoneNumber() const {
	return phoneNumber;
}

void Person::setEmail(string email) {
	this->email = email;
}

string Person::getEmail() const {
	return email;
}
string Person::printInfo() {
	stringstream ss;
	ss << "A minha info é: " << name << endl << age << endl << phoneNumber
			<< endl << email;
	return ss.str();
}

