#ifndef CURRENT_H_
#define CURRENT_H_

#include "../Date.h"
#include "Borrow.h"

class Current: public Borrow {
private:
	Date expectedDeliveryDate;

public:
	Current(Book* book, Employee* employee, Reader* reader, Date borrowDate,
			Date expectedDeliveryDate);

	float CalcFee();
	~Current();
};

#endif
