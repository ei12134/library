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
	int age;
	string email;
	string name;
	unsigned long phoneNumber;
public:
	Person(string name,int age,unsigned long phoneNumber,string email);
	virtual ~Person();
	void setName(string name);
	string getName()const;
	void setAge(int age);
	int getAge()const;
	void setPhoneNumber(unsigned long phoneNumber);
	unsigned long getPhoneNumber()const;
	void setEmail(string email);
	string getEmail()const;
	virtual string printInfo();

};



#endif /* PERSON_H_ */
