// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		AmaApp.h
#ifndef AMA_AMAAPP_H
#define AMA_AMAAPP_H
#include "iProduct.h"

namespace ama {
	
	class AmaApp {
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;
	public:
		AmaApp(const char *);
		~AmaApp();
		int run();
	private:
		AmaApp(const AmaApp&) = delete;
		AmaApp& operator=(const AmaApp&) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords();
		void listProducts();
		void deleteProductRecord(iProduct* product);
		void sort();
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);
	};
}

#endif