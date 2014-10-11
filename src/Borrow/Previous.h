#ifndef PREVIOUS_H_
#define PREVIOUS_H_

#include "Borrow.h"

class Previous: public Borrow {
private:
	float fee;

public:
	Previous(Book* book, Employee* employee, Reader* reader, Data borrowDate,
			Data expectedDeliveryDate, float fee);

	float CalcFee();
	~Previous();
};

#endif
