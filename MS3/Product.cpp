#define _CRT_SECURE_NO_WARNINGS
// Milestone:	3
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Product.cpp
#include "Product.h"
#include <cstring>

namespace ama {
	void Product::message(const char* pText) {
		ErrorState::message(pText);
	}
	bool Product::isClear() const {
		bool check = false;
		if (!*this)
			check = true;
		return check;
	}
	//Product::Product(char type_n) : ErrorState() {

	//}
	Product::Product(const char* sku_n, const char* name_n, const char* unit_n, double costBeforeTax_n,
		int qtyNeed_n, int qtyAvail_n, bool taxable_n) :type('N') {
		if (name_n == nullptr) {
			this->ErrorState::message(nullptr);
		}
		else {
			int len = strlen(name_n);
			name = new char[len + 1];
			strncpy(name, name_n, len);
			name[len] = '\0';
			strncpy(sku, sku_n, max_length_sku);
			strncpy(unit, unit_n, max_length_unit);
			costBeforeTax = costBeforeTax_n;
			qtyNeed = qtyNeed_n, qtyAvail = qtyAvail_n;
			taxable = taxable_n;
		}
	}
	Product::Product(const Product& source) :type('N') {
		name = nullptr;
		*this = source;
	}
	Product& Product::operator=(const Product& src) {
		if (this != &src) {
			strncpy(sku, src.sku, max_length_sku);
			strncpy(unit, src.unit, max_length_unit);
			costBeforeTax = src.costBeforeTax;
			qtyNeed = src.qtyNeed, qtyAvail = src.qtyAvail;
			taxable = src.taxable;
			//*this = Product(src.sku, src.name, src.unit, src.costBeforeTax, src.qtyNeed, src.qtyAvail, src.taxable);
			delete[] name;
			int len = strlen(src.name);
			name = new char[len + 1];
			strncpy(name, src.name, len);
			name[len] = '\0';
		}
		return *this;
	}
	Product::~Product() {
		delete[] name;
		name = nullptr;
	}
	int Product::operator+=(int cnt) {
		if (cnt > 0)
			qtyAvail += cnt;
		return qtyAvail;
	}
	bool Product::operator==(const char* sku_n) const {
		return strncmp(sku, sku_n, max_length_sku);
	}
	bool Product::operator>(const char* sku_n) {
		bool greater = false;
		int check = strncmp(sku, sku_n, max_length_sku);
		if (check > 0)
			greater = true;
		return greater;
	}
	bool Product::operator>(const Product &src) const {
		bool greater = false;
		int check = strncmp(name, src.name, max_length_name);
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
		return qtyAvail * costBeforeTax + (qtyAvail * costBeforeTax * tax_rate);
	}
	bool Product::isEmpty() const {
		return !*this;
	}
	std::istream& Product::read(std::istream& in, bool interractive) {
		char sku_n[max_length_sku + 1];
		char unit_n[max_length_unit + 1];
		char name_n[max_name_length];
		int qtyAvail_n, qtyNeed_n;
		double costBeforeTax_n, costAfterTax_n;
		char taxable_n;
		if (!interractive) {
			in.get(sku_n, max_length_sku, ',');
			in.ignore();
			in.get(name_n, max_name_length, ',');
			in.ignore();
			in.get(unit_n, max_length_unit, ','); in.ignore(); in >> costBeforeTax_n; in.ignore();
			in.ignore(); in >> taxable_n; in.ignore(); in >> qtyAvail_n; in.ignore(); in >> qtyNeed_n; in.ignore();
		}
		if (interractive) {

			bool check = true;
			in.setf(std::ios::right);
			in.width(max_length_label);
			std::cout << "Sku: "; std::cin >> sku_n;
			in.width(max_length_label);
			std::cout << "Name (no spaces): "; std::cin >> name_n;
			in.width(max_length_label);
			std::cout << "Unit: "; std::cin >> unit_n;
			in.width(max_length_label);
			std::cout << "Taxed? (y/n): "; std::cin >> taxable_n;
			if (taxable_n == 'Y' || taxable_n == 'y' || taxable_n == 'N' || taxable_n == 'n')
				check = true;
			else {
				check = false;
				in.setstate(std::ios::failbit);
				this->ErrorState::message("Only (Y)es or (N)o are acceptable!");
			}
			if (check) {
				in.width(max_length_label);
				std::cout << "Price: "; std::cin >> costBeforeTax_n;
				if (in.fail()) {
					check = false;
					in.setstate(std::ios::failbit);
					this->ErrorState::message("Invalid Price Entry!");
				}
				if (check) {
					in.width(max_length_label);
					std::cout << "Quantity on Hand: "; std::cin >> qtyAvail_n;
					if (in.fail() || qtyAvail_n < 1) {
						check = false;
						in.setstate(std::ios::failbit);
						this->ErrorState::message("Invalid Quantity Available Entry!");
					}
					if (check) {
						in.width(max_length_label);
						std::cout << "Quantity needed: "; std::cin >> qtyNeed_n;
						if (in.fail() || qtyNeed_n < 1) {
							check = false;
							in.setstate(std::ios::failbit);
							this->ErrorState::message("Invalid Quantity Needed Entry!");
						}
					}
				}
			}
			in.unsetf(std::ios::right);
		}
		return in;
	}
	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (*this) 
			out << *this;
		if (writeMode == write_condensed && *this) {
			out << type << "," << sku << "," << name << "," << unit << "," << costBeforeTax << taxable
				<< "," << qtyAvail << "," << qtyNeed << std::endl;
		}
		if (writeMode == write_table && *this) {
			out << " "; out.setf(std::ios::right); out.width(max_length_sku); out << sku; out.unsetf(std::ios::right);
			out << " | "; out.setf(std::ios::left);
			if (strlen(name) > max_name_length) {
				out.width(max_name_length - 3); out << name << "... | ";
			}
			else {
				out.width(max_name_length); out << name << " | ";
			}
			out.width(max_length_unit); out << unit; out.unsetf(std::ios::left); out.setf(std::ios::right);
			out.precision(2); out.width(max_length_sku); out << costBeforeTax; 
			if (taxable == 'y' || taxable == 'Y') 
				out << "yes";
			else
				out << "no";
			out.precision(6); out << qtyAvail; out.precision(6); out << qtyNeed; out.unsetf(std::ios::right);
		}
		if (writeMode == write_human && *this) {
			out.setf(std::ios::right); out.width(max_length_label); out << "Sku: " << sku << std::endl;
			out.width(max_length_label); out << "Name: " << name << std::endl;
			out.width(max_length_label); out << "Price: " << costBeforeTax << std::endl;
			out.width(max_length_label); out << "Price after tax: " << total_cost() << std::endl;
			out.width(max_length_label); out << "Quantity Available: " << qtyAvail << std::endl;
			out.width(max_length_label); out << "Quantity Needed: " << qtyNeed << std::endl;
			out.unsetf(std::ios::right);
		}
		return out;
	}
}