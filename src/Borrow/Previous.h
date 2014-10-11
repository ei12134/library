#ifndef PREVIOUS_H_
#define PREVIOUS_H_

#include "../Date.h"
#include "Borrow.h"

class Previous: public Borrow {
private:
	float fee;

public:
	Previous(Book* book, Employee* employee, Reader* reader, Date borrowDate,
			Date expectedDeliveryDate, float fee);

	float CalcFee();
	~Previous();
};

#endif
