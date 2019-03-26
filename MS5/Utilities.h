// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Utilities.h
#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H
#include "Perishable.h"

namespace ama {
	double& operator+=(double& total, const iProduct& prod);
	std::ostream& operator<<(std::ostream& out, const iProduct& prod);
	std::istream& operator>>(std::istream& in, iProduct& prod);
	iProduct* createInstance(char tag);
}

#endif
