// Milestone:	1
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Date.h
#ifndef AMA_DATE_H
#define AMA_DATE_H
#endif
#include <iostream>
using namespace std;
namespace ama {
	const int min_year = 2019, max_year = 2028, no_error = 0, error_year = 1,
		error_mon = 2, error_day = 3, error_invalid_operation = 4, error_input = 5;
	class Date {
		int year, month, day, status;
		void status(int newStatus);
		int mdays(int year, int month) const;
	public:
		Date();
		Date(int yr, int mh, int dy);
		int status() const;
		void clearError();
		bool isGood()const;
		Date& operator+=(int days);
		Date& operator++();
		Date& operator++(int);
		Date& operator+(int days);
		bool operator==(const Date& rhs)const;
		bool operator!=(const Date& rhs);
		bool operator<(const Date& rhs);
		bool operator>(const Date& rhs);
		bool operator<=(const Date& rhs);
		bool operator>=(const Date& rhs);
		istream& read(istream& is);
		ostream& write(ostream& os);
	};
	ostream& operator<<(Date&, ostream&);
	istream& operator>>(Date& rhs, istream&);
}
