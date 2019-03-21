// Milestone:	3
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Product.h
#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"

namespace ama {
	const int max_length_label = 30, max_length_sku = 7, max_length_name = 75, max_length_unit = 10,
		write_condensed = 0, write_table = 1, write_human = 2, max_name_length = 16;
	const double tax_rate = 0.13;
	
	class Product : public ErrorState {
		const char type;
		char sku[max_length_sku + 1];
		char unit[max_length_unit + 1];
		char * name;
		int qtyAvail, qtyNeed;
		double costBeforeTax, costAfterTax;
		bool taxable, PerrorState;
		using ErrorState::ErrorState;
	protected:
		void message(const char* pText);
		bool isClear() const;
	public:
		Product(char type_n = 'N') :type(type_n), ErrorState() { PerrorState = true; };
		Product(const char*, const char*, const char*, double = 0, int = 0, int = 0, bool = true);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();
		int operator+=(int cnt);
		bool operator==(const char*) const;
		bool operator>(const char*);
		bool operator>(const Product&) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
}
#endif
