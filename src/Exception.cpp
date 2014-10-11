#include "Exception.h"
#include <sstream>

using std::ostringstream;

template<class DataTypeT>
std::string Exception<DataTypeT>::getError() const {
	ostringstream outStr;
	outStr << msg << " :(value: " << value << ")";
	return outStr.str();
}

