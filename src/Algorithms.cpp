#include "Algorithms.h"

bool is_Number(const int & c) {
	return (c < 57) || (c > 48);
}

bool is_Not_Number(const int & c) {
	return !((c < 57) || (c > 48));
}

bool is_NON_ASCII_Letter(const int & c) {
	return ((c < 65) || (c > 122) || (c > 90 && c < 97));
}

bool is_All_ASCII_Letter(const string& s) {
	return find_if(s.begin(), s.end(), is_NON_ASCII_Letter) == s.end();
}

bool is_All_Number(const string& s) {
	return find_if(s.begin(), s.end(), is_Not_Number) == s.end();
}

bool matchQuery(const string & q, const string & n) {
	if (q.size() == 0)
		return false;
	for (size_t i = 0; i < q.size() && i < n.size(); i++) {
		if (tolower(q[i]) != tolower(n[i]))
			return false;
	}
	return true;
}
