// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Perishable.h

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H
#include "Date.h"
#include "Product.h"

namespace ama {
	class Perishable : public Product {
		Date currentDate;
	public:
		Perishable() : Product('P') {};
		std::ostream& write(std::ostream& out, int writeMode) const;
		std::istream& read(std::istream& in, bool interractive);
	};
}
#endif
