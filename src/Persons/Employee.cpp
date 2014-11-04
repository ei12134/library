#include "Employee.h"

Employee::Employee(string name, unsigned int age, unsigned int phoneNumber,
		string email, unsigned int nif, unsigned int wage, bool supervisor) :
		Person(name, age, phoneNumber, email) {
	this->nif = nif;
	this->wage = wage;
	this->supervisor = supervisor;
}

Employee::Employee(ifstream& s, bool superv) :
		Person(s) {
	stringstream ss;
	string sNif, sWage, sSupervisor;
	unsigned int nif, wage;

	getline(s, sNif, ';');
	ss << sNif;
	ss >> nif;
	ss.clear();
	this->nif = nif;

	if (!superv) // read last input until newline
		getline(s, sWage);
	else
		getline(s, sWage, ';');
	ss << sWage;
	ss >> wage;
	ss.clear();
	this->wage = wage;

	this->supervisor = superv;
}

void Employee::saveData(ofstream &of) {
	Person::saveData(of);
	of << nif << ";" << wage;
	if (supervisor) {
		of << ";";
		if (team.size() > 0)
			of << team[0]->getName();
		for (unsigned x = 1; x < team.size(); x++) {
			of << "," << team[x]->getName();
		}
	}
	// nao poem endl
}

Employee::~Employee() {
}

void Employee::addEmplyee(Employee * e) {
	if (supervisor)
		this->team.push_back(e);
}

vector<Borrow*> Employee::getBorrowedBooks() const {
	vector<Borrow*> empty;
	return empty;
}

unsigned int Employee::getNif() const {
	return nif;
}

void Employee::setNif(unsigned int nif) {
	this->nif = nif;
}

unsigned int Employee::getWage() const {
	return wage;
}

void Employee::setWage(unsigned int wage) {
	this->wage = wage;
}

void createBorrow(Book *, Reader *, Employee *) {
}

string Employee::print() const {
	stringstream ss;
	ss << Person::print();

	if (email.size() >= 22)
		ss << "\t";
	else
		for (int i = 24 - email.size(); i > 0; i -= 8)
			ss << "\t";

	stringstream nifStr;
	nifStr << nif;
	string nifS = nifStr.str();
	ss
			<< ("*"
					+ (nifS.size() > 3 ?
							nifS.substr(nifS.size() - 3, nifS.size()) : nifS));

//	if (supervisor) {
//		ss << "   ";
//		if (team.size() > 0)
//			ss << team[0]->getName();
//		for (unsigned x = 1; x < team.size(); x++) {
//			ss << "   " << team[x]->getName();
//		}
//	}
	return ss.str();
}

unsigned int Employee::getType() const {
	if (!supervisor)
		return 2;
	else
		return 3;
}

void Employee::setSupervisor(bool super) {
	this->supervisor = super;
}

bool Employee::isSupervisor() const {
	return supervisor;
}

unsigned int Employee::getCard() const {
	return 0;
}

string Employee::printType() const {
	if (!supervisor)
		return "[Employee]";
	else
		return "[Supervisor]";
}

bool Employee::removeBorrow(Borrow* borrow) {
	return false;
}

void Employee::addBorrow(Borrow* borrow){

}
