#ifndef PERSON_H_
#define PERSON_H_

class Employee;
class Borrow;

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
	Person(string name, unsigned int age, unsigned int phone, string email);
	Person(ifstream& s);
	virtual ~Person();

	virtual void saveData(ofstream &of) = 0;
	virtual string print() const;
	virtual unsigned int getType() const = 0;
	virtual unsigned int getCard() const = 0;
	virtual unsigned int getNif() const = 0;
	virtual unsigned int getWage() const = 0;
	virtual bool removeBorrow(Borrow* borrow) = 0;
	virtual bool addBorrow(Borrow* borrow) = 0;
	virtual vector<Borrow*> getBorrowedBooks() const = 0;
	virtual vector<Employee *>getEmployeeTeam() const;

	virtual string printType() const = 0;
	void setName(string name);
	void setAge(unsigned int age);
	void setPhone(unsigned int phoneNumber);
	void setEmail(string email);
	virtual void setNif(unsigned int nif) {
	}
	virtual void setWage(unsigned int wage) {
	}
	virtual void setSupervisor(bool super) {
	}
	string getName() const;
	string getEmail() const;
	unsigned int getAge() const;
	unsigned int getPhone() const;
};

#endif /* PERSON_H_ */
