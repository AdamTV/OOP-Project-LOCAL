#define _CRT_SECURE_NO_WARNINGS
// Milestone:	4
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Product.cpp
#include "Product.h"
#include <cstring>

namespace ama {
	const char* Product::name() const {
		return currentName;
	}
	void Product::message(const char* pText) {
		errorState.message(pText);
	}
	bool Product::isClear() const {
		bool check = false;
		if (!errorState)
			check = true;
		return check;
	}
	Product::Product(const char* sku_n, const char* name_n, const char* unit_n, double costBeforeTax_n,
		int qtyNeed_n, int qtyAvail_n, bool taxable_n) :type('N') {
		if (name_n == nullptr) {
			currentName = nullptr;
			PSafeEmptyState = true;
			errorState.message(nullptr);
		}
		else {
			int len = strlen(name_n);
			currentName = new char[len + 1];
			strncpy(currentName, name_n, len);
			currentName[len] = '\0';
			strncpy(sku, sku_n, max_length_sku);
			strncpy(unit, unit_n, max_length_unit);
			costBeforeTax = costBeforeTax_n;
			qtyNeed = qtyNeed_n, qtyAvail = qtyAvail_n;
			taxable = taxable_n;
			PSafeEmptyState = false;
		}
	}
	Product::Product(const Product& source) :type('N') {
		currentName = nullptr;
		*this = source;
	}
	Product& Product::operator=(const Product& src) {
		if (this != &src) {
			PSafeEmptyState = src.PSafeEmptyState;
			strncpy(sku, src.sku, max_length_sku);
			strncpy(unit, src.unit, max_length_unit);
			costBeforeTax = src.costBeforeTax;
			qtyNeed = src.qtyNeed, qtyAvail = src.qtyAvail;
			taxable = src.taxable;
			delete[] currentName;
			currentName = nullptr;
			int len = strlen(src.currentName);
			currentName = new char[len + 1];
			strncpy(currentName, src.currentName, len);
			currentName[len] = '\0';
		}
		return *this;
	}
	Product::~Product() {
		delete[] currentName;
		currentName = nullptr;
	}
	int Product::operator+=(int cnt) {
		if (cnt > 0)
			qtyAvail += cnt;
		return qtyAvail;
	}
	bool Product::operator==(const char* sku_n) const {
		bool check = false;
		if (strncmp(sku, sku_n, max_length_sku) == 0)
			check = true;
		return check;
	}
	bool Product::operator>(const char* sku_n) {
		bool greater = false;
		int check = strncmp(sku, sku_n, max_length_sku);
		if (check > 0)
			greater = true;
		return greater;
	}
	bool Product::operator>(const iProduct &src) const {
		bool greater = false;
		int check = strncmp(currentName, src.name(), max_length_name);
		if (check > 0)
			greater = true;
		return greater;
	}
	int Product::qtyAvailable() const {
		return qtyAvail;
	}
	int Product::qtyNeeded() const {
		return qtyNeed;
	}
	double Product::total_cost() const {
		double total = costBeforeTax + (costBeforeTax * tax_rate);
		if (!taxable)
			total = costBeforeTax;
		total *= qtyAvail;
		return total;
	}
	bool Product::isEmpty() const {
		return PSafeEmptyState;
	}
	std::istream& Product::read(std::istream& in, bool interractive) {
		char sku_n[max_length_sku + 1];
		char unit_n[max_length_unit + 1];
		char name_n[max_length_name];
		const char* sku_x = sku_n;
		const char* unit_x = unit_n;
		const char* name_x = name_n;
		int qtyAvail_n, qtyNeed_n;
		double costBeforeTax_n;
		bool taxable_n;
		char taxitem;
		if (!interractive) {
			in.get(sku_n, max_length_sku, ',');
			in.ignore();
			in.get(name_n, max_length_name, ',');
			in.ignore();
			in.get(unit_n, max_length_unit, ','); in.ignore();
			in >> costBeforeTax_n;
			in.ignore();
			in >> taxable_n;
			in.ignore();
			in >> qtyAvail_n;
			in.ignore();
			in >> qtyNeed_n;
			in.ignore();
			Product tmp(sku_x, name_x, unit_x, costBeforeTax_n, qtyNeed_n, qtyAvail_n, taxable_n);
			*this = tmp;
		}
		if (interractive) {

			bool check = true;
			std::cout.setf(std::ios::right);
			std::cout.width(max_length_label);
			std::cout << "Sku: "; std::cin >> sku_n;
			std::cout.width(max_length_label);
			std::cout << "Name (no spaces): "; std::cin >> name_n;
			std::cout.width(max_length_label);
			std::cout << "Unit: "; std::cin >> unit_n;
			std::cout.width(max_length_label);
			std::cout << "Taxed? (y/n): "; std::cin >> taxitem;
			if (taxitem == 'Y' || taxitem == 'y')
				taxable_n = true;
			else if (taxitem == 'N' || taxitem == 'n')
				taxable_n = false;
			else {
				check = false;
				in.setstate(std::ios::failbit);
				errorState.message("Only (Y)es or (N)o are acceptable!");
			}
			if (check) {
				std::cout.width(max_length_label);
				std::cout << "Price: "; std::cin >> costBeforeTax_n;
				if (in.fail()) {
					check = false;
					in.setstate(std::ios::failbit);
					errorState.message("Invalid Price Entry!");
				}
				if (check) {
					std::cout.width(max_length_label);
					std::cout << "Quantity on Hand: "; std::cin >> qtyAvail_n;
					if (in.fail() || qtyAvail_n < 1) {
						check = false;
						in.setstate(std::ios::failbit);
						errorState.message("Invalid Quantity Available Entry!");
					}
					if (check) {
						std::cout.width(max_length_label);
						std::cout << "Quantity needed: "; std::cin >> qtyNeed_n;
						if (in.fail() || qtyNeed_n < 1) {
							check = false;
							in.setstate(std::ios::failbit);
							errorState.message("Invalid Quantity Needed Entry!");
						}
						if (check) {
							Product tmp(sku_x, name_x, unit_x, costBeforeTax_n, qtyNeed_n, qtyAvail_n, taxable_n);
							*this = tmp;
						}
					}
				}
			}
			std::cout.unsetf(std::ios::right);
		}
		return in;
	}
	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (errorState)
			out << errorState;
		else if (!(isEmpty())) {
			if (writeMode == write_condensed) {
				out.setf(std::ios::fixed); out.precision(2);
				out << type << "," << sku << "," << currentName << "," << unit << "," << costBeforeTax << "," << taxable
					<< "," << qtyAvail << "," << qtyNeed;	//out.unsetf(std::ios::fixed); out.precision(6);
			}
			else if (writeMode == write_table) {
				out << " "; out.setf(std::ios::right); out.width(max_length_sku);
				out << sku; out.unsetf(std::ios::right);
				out << " | "; out.setf(std::ios::left);
				if (strlen(currentName) > max_name_length) {
					char newName[14];
					strncpy(newName, currentName, 13);
					newName[13] = '\0';
					out << newName;
					out << "... | ";
				}
				else {
					out.width(max_name_length); out << currentName << " | ";
				}
				out.width(max_length_unit); out << unit << " | "; 
				out.unsetf(std::ios::left);
				out.setf(std::ios::right);
				out.setf(std::ios::fixed);
				out.precision(2); out.width(max_length_sku); out << costBeforeTax;
				if (taxable)
					out << " | yes | ";
				else
					out << " | no | ";
				out.width(6);
				out << qtyAvail << " | ";
				out.width(6);
				out << qtyNeed << " |";
				out.unsetf(std::ios::fixed);
				out.unsetf(std::ios::right);
			}
			else if (writeMode == write_human) {
				double afterTax = (total_cost() / qtyAvail);
				if (qtyAvail == 0)
					afterTax = 0;
				out.setf(std::ios::fixed); out.precision(2);
				out.setf(std::ios::right); out.width(max_length_label); out << "Sku: " << sku << std::endl;
				out.width(max_length_label); out << "Name: " << currentName << std::endl;
				out.width(max_length_label); out << "Price: " << costBeforeTax << std::endl;
				out.width(max_length_label); out << "Price after Tax: " << afterTax << std::endl;
				out.width(max_length_label); out << "Quantity Available: " << qtyAvail << " " << unit << std::endl;
				out.width(max_length_label); out << "Quantity Needed: " << qtyNeed << " " << unit << std::endl;
				out.precision(6);
				out.unsetf(std::ios::right);
				out.unsetf(std::ios::fixed);
			}
		}
		return out;
	}
}
