// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		AmaApp.cpp

#include "AmaApp.h"
using namespace std;

namespace ama {
	const int max_filename_size = 14, products = 100;
	AmaApp::AmaApp(const char * filename) {
		strncpy(m_filename, filename, max_filename_size);
		for(int i = 0; i < products; i++)
			m_products[i] = nullptr;
		m_noOfProducts = 0;
	}
	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++) {
			delete[] m_products[i];
			m_products[i] = nullptr;
		}
	}
	int AmaApp::run() {

	}
	void AmaApp::pause() const {
		std::cout << "Press Enter to continue...\n";
		std::cin.ignore(2000, '\n');
	}
	int	AmaApp::menu() const {
		cout.fill('-') << setw(38) << '-';
	}
	void AmaApp::loadProductRecords() {

	}
	void AmaApp::saveProductRecords() {

	}
	void AmaApp::listProducts() {

	}
	void AmaApp::deleteProductRecord(iProduct* product) {

	}
	iProduct* AmaApp::find(const char* sku) const {

	}
	void AmaApp::addQty(iProduct* product) {

	}
	void AmaApp::addProduct(char tag) {

	}
}