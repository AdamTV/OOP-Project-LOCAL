// Milestone:	3
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Utilities.h
#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H
#include "Product.h"

namespace ama {
	double& operator+=(double& total, const Product& prod);
	std::ostream& operator<<(std::ostream& out, const Product& prod);
	std::istream& operator>>(std::istream& in, Product& prod);
}

#endif
