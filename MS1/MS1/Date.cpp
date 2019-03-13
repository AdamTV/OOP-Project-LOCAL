// Milestone:	1
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Date.cpp

#include "Date.h"

namespace ama {
	void Date::status(int newStatus) {
		this->status = newStatus;
	}
	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	Date::Date() {
		this->status = no_error;
		year = 0, month = 0, day = 0;
	}
	Date::Date(int yr, int mh, int dy) {
		bool valid = true;
		if (year < min_year || year > max_year) {
			valid = false;
			Date();
			this->status = error_year;
		}
		if (month < 1 || month > 12) {
			valid = false;
			Date();
			this->status = error_mon;
		}
		if (day > mdays(year, month) || day < mdays(year, month)) {
			valid = false;
			Date();
			this->status = error_day;
		}
		if (valid) {
			year = yr, month = mh, day = dy;
			this->status = no_error;
		}
	}
	int Date::status() const {
		return this->status;
	}
	void Date::clearError() {
		this->status = no_error;
	}
	bool Date::isGood() const {
		bool valid = false;
			if (this->status == no_error && year != 0 && month != 0 && day != 0)
				valid = true;
		return valid;
	}
	Date& Date::operator+=(int days) {
		if (isGood() && day + days <= (mdays(year, month)))
			day += days;
		else
			this->status = error_invalid_operation;
		return *this;
	}
	Date& Date::operator++() {
		if (isGood() && ++day <= (mdays(year, month)))
			++day;
		else
			this->status = error_invalid_operation;
		return *this;
	}
	Date& Date::operator++(int) {
		if (isGood() && day++ <= (mdays(year, month)))
			day++;
		else
			this->status = error_invalid_operation;
		return *this;
	}
	Date& Date::operator+(int days) {
		if (isGood() && day + days <= (mdays(year, month)))
			Date(year, month, (day + days));
		else
			this->status = error_invalid_operation;
		return *this;
	}
	bool Date::operator==(const Date& rhs) const{
		bool valid = false;
		if (year == rhs.year && month == rhs.month && day == rhs.day)
			valid = true;
		return valid;
	}
	bool Date::operator!=(const Date& rhs) {
		bool valid = true;
		if (*this == rhs)
			valid = false;
		return valid;
	}
	bool Date::operator<(const Date& rhs) {
		bool valid = false;
		if (year < rhs.year)
			valid = true;
		else if (year == rhs.year) {
			if (month < rhs.month)
				valid = true;
			else if (month == rhs.month) {
				if (day < rhs.day)
					valid = true;
			}
		}
		return valid;
	}
	bool Date::operator>(const Date& rhs) {
		bool valid = true;
		if (*this < rhs)
			valid = false;
		return valid;
	}
	bool Date::operator<=(const Date& rhs) {
		bool valid = false;
		if (*this < rhs || *this == rhs)
			valid = true;
		return valid;
	}
	bool Date::operator>=(const Date& rhs) {
		bool valid = false;
		if (*this > rhs || *this == rhs)
			valid = true;
		return valid;
	}
	istream& Date::read(istream& is) {
		bool valid = true;
		is >> year;
		if (is.fail())
			valid = false;
		is.ignore();
		is >> month;
		if (is.fail())
			valid = false;
		is.ignore();
		is >> day;
		if (is.fail())
			valid = false;
		if (valid == false) {
			*this = Date();
			this->status = error_input;
		}
		return is;
	}
	ostream& Date::write(ostream& os) {
		os << year << "/" << month << "/" << day;
		return os;
	}
	ostream& operator<<(Date& rhs, ostream& os)
	{
		rhs.write;
		return os;
	}
	istream& operator>>(Date& rhs, istream& is){
		rhs.read;
		return is;
	}
}