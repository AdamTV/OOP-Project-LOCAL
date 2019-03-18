// Milestone:	3
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Utilities.cpp
#include "Utilities.h"

namespace ama {
	double& operator+=(double& total, const Product& prod) {
		double total_n = total + prod.total_cost();
		return total_n;
	}
	std::ostream& operator<<(std::ostream& out, const Product& prod) {
		prod.write(out, write_human);
		return out;
	}
	std::istream& operator>>(std::istream& in, Product& prod) {
		prod.read(in, true);
		return in;
	}
}