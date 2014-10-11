#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

#include "Library.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Interface {
public:
	Interface();
	template<typename T>
	void displayContainer(vector<T*> container) const;
	virtual ~Interface();

private:
	Library library;
};

#endif /* SRC_INTERFACE_H_ */
