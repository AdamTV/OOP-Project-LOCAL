// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		AmaApp.cpp

#include <iomanip>
#include <fstream>
#include "Utilities.h"
#include "AmaApp.h"

using namespace std;

namespace ama {

	const int max_filename_size = 14, products = 100;

	AmaApp::AmaApp(const char * filename) {
		strncpy(m_filename, filename, max_filename_size);
		for(int i = 0; i < products; i++)
			m_products[i] = nullptr;
		m_noOfProducts = 0;
		loadProductRecords();
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
		int choice = -1;
		cout << "Disaster Aid Supply Management Program\n" 
			 << setfill('-') << setw(38) << '-' <<
			"\n1- List products\n"
			"2- Search product\n"
			"3- Add non-perishable product\n"
			"4- Add perishable product\n"
			"5- Add to product quantity\n"
			"6- Delete product\n"
			"7- Sort products\n"
			"0- Exit program\n> ";
		cin >> choice;
		cin.ignore(2000, '\n'); //NOT SURE
		return choice;
	}
	void AmaApp::loadProductRecords() {
		int i;
		char tag;
		if (m_noOfProducts > 0) {
			for (int i = 0; i < m_noOfProducts; i++) {
				delete[] m_products[i];
				m_products[i] = nullptr;
			}
		}
		m_noOfProducts = 0;
		ios::in;
		ifstream fin("inventory.txt");
		if (fin.is_open()) {
			for (i = 0; !fin.fail(); i++) {
				fin.get(tag);
				if (createInstance(tag) != nullptr) {
					fin.ignore();
					m_products[i] = createInstance(tag);
					m_products[i]->read(fin, false);
				}
			}
			m_noOfProducts = i;
			fin.close();
		}
	}
	void AmaApp::saveProductRecords() {
		
	}
	void AmaApp::listProducts() {
		cout << setw(96) << "-" << endl
			<< "| Row |";
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