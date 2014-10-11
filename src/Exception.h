#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>

template<class DataTypeT>
class Exception {
private:
	std::string msg;
	DataTypeT value;
public:

	Exception(std::string str, DataTypeT value) :
			msg(str), value(value) {
	}

	std::string getError() const;

	std::string getMessage() const {
		return msg;
	}
	DataTypeT getValue() const {
		return value;
	}
};

#endif
