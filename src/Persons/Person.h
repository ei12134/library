/*
 * Person.h
 *
 *  Created on: 8 de Out de 2014
 *      Author: zikoc_000
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Person {
	unsigned int age, phone;
	string email;
	string name;
public:
	Person(string name, unsigned int age, unsigned int phone, string email);
	Person(fstream& s);
	virtual ~Person();
	virtual string print();
	void setName(string name);
	void setAge(unsigned int age);
	void setPhone(unsigned int phoneNumber);
	void setEmail(string email);
	string getName() const;
	string getEmail() const;
	unsigned int getAge() const;
	unsigned int getPhone() const;
};

#endif /* PERSON_H_ */
