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
				out.setf(std::ios::right); out.width(max_length_label);
				out << "Expiry Date: ";
				Date::write; out << std::endl; out.unsetf(std::ios::right);
			}
			if (writeMode == write_table) {
				out << " " << currentDate.write << " |";
			}
			if (writeMode == write_condensed) {
				out << ", " << currentDate.write;
			}
		}
	}
	std::istream& Perishable::read(std::istream& in, bool interractive) {
		Product::read(in, interractive);
		if (interractive) {
			std::cout.setf(std::ios::right); std::cout.width(max_length_label);
			std::cout << "Expiry date (YYYY/MM/DD): ";
			std::cout.unsetf(std::ios::right);
			currentDate.read;
			if (!isClear()) {
				in.setstate(std::ios::failbit);
				Product::message("Invalid Date Entry");
			}
		}
		if (!interractive) {
			currentDate.read;
			in.ignore();
		}
	}
}