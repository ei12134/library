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
protected:
	unsigned int age, phone;
	string email;
	string name;
public:
	Person(fstream& s);
	Person(string name, unsigned int age, unsigned int phone,
			string email);
	virtual ~Person();
	void setName(string name);
	string getName() const;
	void setAge(unsigned int age);
	unsigned int getAge() const;
	void setPhone(unsigned int phoneNumber);
	unsigned int getPhone() const;
	void setEmail(string email);
	string getEmail() const;
	virtual string print();
	virtual void load(fstream& s);

};

#endif /* PERSON_H_ */
