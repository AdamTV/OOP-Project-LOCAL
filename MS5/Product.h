// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Product.h

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"
#include "iProduct.h"

namespace ama {

	
	class Product : public iProduct {
		const char type;
		char sku[max_length_sku + 1];
		char unit[max_length_unit + 1];
		char * currentName;
		int qtyAvail, qtyNeed;
		double costBeforeTax, costAfterTax;
		bool taxable, PSafeEmptyState;
		ErrorState errorState;
	protected:
		void message(const char* pText);
		bool isClear() const;
		void empty();
	public:
		Product(char type_n = 'N') : type(type_n) { PSafeEmptyState = true; currentName = nullptr; };
		Product(const char*, const char*, const char*, double = 0, int = 0, int = 0, bool = true);
		Product(const Product&);
		Product& operator=(const Product&);
		virtual ~Product();
		int operator+=(int cnt);
		bool operator==(const char*) const;
		bool operator>(const char*);
		bool operator>(const iProduct&) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		const char* name() const;
		double total_cost() const;
		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
}
#endif
