#include "Interface.h"

Interface::Interface() {
	this->library = Library();
	displayContainer(library.getReaders());
}

Interface::~Interface() {
	// TODO Auto-generated destructor stub
}

template<typename T>
void Interface::displayContainer(vector<T*> container) const {
	typename vector<T*>::const_iterator it;
	for (it = container.begin(); it != container.end(); it++) {
		string print = (*it)->print();
		cout << print << endl;
	}
}
