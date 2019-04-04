#define _CRT_SECURE_NO_WARNINGS
// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		AmaApp.cpp

#include <cstring>
#include <iomanip>
#include <fstream>
#include "Utilities.h"
#include "AmaApp.h"
#include "Sort.h"

using namespace std;

namespace ama {

	const int max_filename_size = 14, products = 100;

	AmaApp::AmaApp(const char * filename) {
		*m_products = nullptr;
		strncpy(m_filename, filename, max_filename_size);
		for(int i = 0; i < products; i++)
			m_products[i] = nullptr;
		m_noOfProducts = 0;
		loadProductRecords();
	}
	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++) {
			delete m_products[i];
			m_products[i] = nullptr;
		}
	}
	int AmaApp::run() {
		bool go = true;
		iProduct* tmp = nullptr;
		do {
			int choice = menu();
			switch (choice)
			{
			case 1:
				listProducts();
				break;
			case 2:
				cout << "Please enter the product SKU: ";
				char tempSKU[max_length_sku + 1];
				cin >> tempSKU;
				std::cin.ignore(2000, '\n');
				tmp = find(tempSKU);
				cout << endl;
				if (tmp != nullptr) {
					tmp->write(cout, write_human);
				}
				else {
					cout << "No such product!";
				}
				cout << endl;
				break;
			case 3:
				addProduct('n');
				loadProductRecords();
				break;
			case 4:
				addProduct('p');
				loadProductRecords();
				break;
			case 5:
				char tmpSKU[max_length_sku + 1];
				cout << "Please enter the product SKU: ";
				cin >> tmpSKU;
				cout << endl;
				std::cin.ignore(2000, '\n');
				tmp = find(tmpSKU);
				if (tmp != nullptr) {
					addQty(tmp);
				}
				else {
					cout << "No such product!\n";
				}
				cout << endl;
				break;
			case 6:
				char tpSKU[max_length_sku + 1];
				cout << "Please enter the product SKU: ";
				cin >> tpSKU;
				cout << endl;
				std::cin.ignore(2000, '\n');
				tmp = find(tpSKU);
				if (tmp != nullptr) {
					deleteProductRecord(tmp);
					loadProductRecords();
					cout << "Deleted!";
				}
				else {
					cout << "No such product!\n";
				}
				cout << endl;
				break;
			case 7:
 				sort();
				saveProductRecords();
				cout << "Sorted!\n\n";
				break;
			case 0:
				cout << "Goodbye!\n";
				go = false;
				break;
			default:
				cout << "~~~Invalid selection, try again!~~~\n";
				break;
			}
			if(choice != 3 && choice != 4 && choice != 5 && choice != 0)
			pause();
		} while (go);
		return 0;
	}
	void AmaApp::pause() const {
		std::cout << "Press Enter to continue...\n";
		std::cin.ignore(2000, '\n');
	}
	int	AmaApp::menu() const {
		int choice;
		cout << "Disaster Aid Supply Management Program\n"
			<< setfill('-') << setw(38) << '-' << setfill(' ') <<
			"\n1- List products\n"
			"2- Search product\n"
			"3- Add non-perishable product\n"
			"4- Add perishable product\n"
			"5- Add to product quantity\n"
			"6- Delete product\n"
			"7- Sort products\n"
			"0- Exit program\n> ";
		cin >> choice;
		cin.ignore(2000, '\n');
		return choice;
	}
	void AmaApp::loadProductRecords() {
		int i;
		char tag = '\0';
		if (m_noOfProducts > 0) {
			for (int i = 0; i < m_noOfProducts; i++) {
				delete m_products[i];
				m_products[i] = nullptr;
			}
		}
		m_noOfProducts = 0;
		ifstream fin(m_filename);
		if (fin.is_open()) {
			for (i = 0; !fin.fail(); i++) {
				if(tag == 'P' || tag == 'p')	
					fin.ignore(2000,'\n');
				fin.get(tag);
				if (createInstance(tag) != nullptr) {
					fin.ignore();
					m_products[i] = createInstance(tag);
					m_products[i]->read(fin, false);
				}
			}
			m_noOfProducts = i - 1;
			fin.close();
		}
	}
	void AmaApp::saveProductRecords() {
		ofstream o(m_filename);
		for (int i = 0; i < m_noOfProducts; i++) {
			m_products[i]->write(o, write_condensed);
			o << endl;
		}
	}
	void AmaApp::listProducts() {
		cout << setfill('-') << setw(96) <<  "-" << endl <<
			"| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |\n"
			"|-----|---------|------------------|------------|---------|-----|--------|--------|------------|"
			<< endl;
		double total = 0;
		for (int i = 0; i < m_noOfProducts; i++) {
			cout << "|" << setfill(' ') << right << setw(4) << i + 1 << " |";
			m_products[i]->write(cout, write_table); cout << endl;
			total += *m_products[i];
		}
		cout << setfill('-') << setw(96) << "-" << endl << setfill(' ') << "|" <<
			setw(82) << "Total cost of support ($): |" << " " << fixed << setprecision(2) 
			<< setw(10) << right << total << " |" <<
			endl << setfill('-') << setw(96) << "-" << endl << endl << setfill(' ') << setprecision(6);
		cout.unsetf(ios::fixed);
	}
	void AmaApp::deleteProductRecord(iProduct* product) {
		ofstream o(m_filename);
		for (int i = 0; i < m_noOfProducts; i++) {
			if (m_products[i] != product) {
				m_products[i]->write(o, write_condensed);
				o << endl;
			}
		}
	}
	void AmaApp::sort()
	{
		sict::sort((m_products), m_noOfProducts);
	}
	iProduct* AmaApp::find(const char* sku) const {
		iProduct* found = nullptr;
		bool check = false;
		for (int i = 0; i < m_noOfProducts && !check; i++) {
			if (*m_products[i] == sku) {
				found = m_products[i];
				check = true;
			}
		}
		return found;
	}
	void AmaApp::addQty(iProduct* product) {
		product->write(cout, write_human); cout << "\n\n"
			"Please enter the number of purchased items: ";
		int number; cin >> number;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(2000, '\n');
			cout << "Invalid quantity value!\n";
		}
		else {
			int required = (product->qtyNeeded() - product->qtyAvailable());
			if (number < required || number == required) {
				*product += number;
			}
			else {
				*product += required;
				cout << "Too many items; only " << required << " is needed. Please return the extra "
					<< number - required << " items.\n";
			}
			saveProductRecords();
			cout << "\nUpdated!\n";
			cin.ignore(2000, '\n');
		}
	}
	void AmaApp::addProduct(char tag) {
		iProduct* temp = createInstance(tag);
		if (temp != nullptr) {
			m_noOfProducts++;
			m_products[m_noOfProducts - 1] = temp;
			cin >> *m_products[m_noOfProducts - 1];

			if (cin.fail()) {
				cin.clear();
				std::cin.ignore(2000, '\n');
				cout << endl << *m_products[m_noOfProducts - 1] << endl << endl;
				m_noOfProducts--;
			}
			else {
				saveProductRecords();
				cout << endl << "Success!" << endl << endl;
			}
		}
	}
}
