// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Perishable.cpp

#include "Perishable.h"

namespace ama {
	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (!isEmpty()) {
			if (writeMode == write_human) {

			}
		}
	}
}