/*
 * Person.cpp
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */
#include "Person.h"

using namespace std;

Person::Person(string name, unsigned int age, unsigned long int phone,
		string email) {
	this->name = name;
	this->age = age;
	this->phone = phone;
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

void Person::setPhone(unsigned long int phone) {
	this->phone = phone;
}

unsigned long int Person::getPhone() const {
	return phone;
}

void Person::setEmail(string email) {
	this->email = email;
}

string Person::getEmail() const {
	return email;
}

string Person::print() {
	stringstream ss;
	ss << name << " ; " << age << " ; "<< phone << " ; " << email;
	return ss.str();
}
