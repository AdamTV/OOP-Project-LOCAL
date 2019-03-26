// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Utilities.cpp
#include "Utilities.h"

namespace ama {
	double& operator+=(double& total, const iProduct& prod) {
		total += prod.total_cost();
		return total;
	}
	std::ostream& operator<<(std::ostream& out, const iProduct& prod) {
		prod.write(out, write_human);
		return out;
	}
	std::istream& operator>>(std::istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}
	iProduct* createInstance(char tag) {
		iProduct* tmp = nullptr;
		if (tag == 'n' || tag == 'N')
			tmp = new Product;
		if (tag == 'p' || tag == 'P')
			tmp = new Perishable;
		return tmp;
	}

}