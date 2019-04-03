// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Perishable.cpp

#include "Perishable.h"

namespace ama {
	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (!(isEmpty())) {
			if (writeMode == write_human) {
				out.setf(std::ios::right); out.width(max_length_label);
				out << "Expiry Date: ";
				currentDate.write(out); out << std::endl; out.unsetf(std::ios::right);
			}
			if (writeMode == write_table) {
				out << " "; currentDate.write(out) << " |";
			}
			if (writeMode == write_condensed) {
				out << ", "; currentDate.write(out);
			}
		}
		return out;
	}
	std::istream& Perishable::read(std::istream& in, bool interractive) {
		Product::read(in, interractive);
		if (interractive) {
			std::cout.setf(std::ios::right); std::cout.width(max_length_label);
			std::cout << "Expiry date (YYYY/MM/DD): ";
			std::cout.unsetf(std::ios::right);
			in >> currentDate;
			if (!currentDate.isGood()) {
				empty();
				in.setstate(std::ios::failbit);
				Product::message("Invalid Date Entry");
				if (currentDate.status() == error_year)
					message("Invalid Year in Date Entry");
				if (currentDate.status() == error_mon)
					message("Invalid Month in Date Entry");
				if (currentDate.status() == error_day)
					message("Invalid Day in Date Entry");
			}
			return in;
		}
		if (!interractive) {
			currentDate.read(in);
			//in.ignore();
		}
		return in;
	}
}
