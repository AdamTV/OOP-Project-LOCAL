// Milestone:	1
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		Date.cpp

#include "Date.h"

namespace ama {
	void Date::status(int newStatus) {
		currentStatus = newStatus;
	}
	int Date::mdays(int year, int mon) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}
	Date::Date() {
		currentStatus = no_error;
		year = 0, month = 0, day = 0;
	}
	Date::Date(int yr, int mh, int dy) {
		bool valid = true;
		if (yr < min_year || yr > max_year) {
			valid = false;
			*this = Date();
			currentStatus = error_year;
		}
		if (valid) {
			if (mh < 1 || mh > 12) {
				valid = false;
				*this = Date();
				currentStatus = error_mon;
			}
			if (valid) {
				if (dy > mdays(yr, mh) || dy < 1) {
					valid = false;
					*this = Date();
					currentStatus = error_day;
				}

				if (valid) {
					year = yr, month = mh, day = dy;
					currentStatus = no_error;
				}
			}
		}
	}
	int Date::status() const {
		return currentStatus;
	}
	void Date::clearError() {
		currentStatus = no_error;
	}
	bool Date::isGood() const {
		bool valid = false;
		if (currentStatus == no_error && year != 0 && month != 0 && day != 0)
			valid = true;
		return valid;
	}
	Date& Date::operator+=(int days) {
		if (isGood() && day + days <= (mdays(year, month)) && day + days > 0)
			day += days;
		else
			currentStatus = error_invalid_operation;
		return *this;
	}
	Date& Date::operator++() {
		if (isGood() && day + 1 <= (mdays(year, month)))
			++day;
		else
			currentStatus = error_invalid_operation;
		return *this;
	}
	Date& Date::operator++(int) {
		Date tmp = *this;
		Date& gotta = tmp;
		if (isGood() && day + 1 <= (mdays(year, month)))
			day++;
		else
			this->currentStatus = error_invalid_operation;
		return gotta;
	}
	Date& Date::operator+(int days)const {
		Date tmp = *this;
		Date& gotta = tmp;
		if (isGood() && day + days <= (mdays(year, month)) && day + days > 0)
			tmp = Date(year, month, (day + days));
		else {
			tmp.currentStatus = error_invalid_operation;
		}
		return gotta;
	}
	bool Date::operator==(const Date& rhs) const {
		bool valid = false;
		if (year == rhs.year && month == rhs.month && day == rhs.day)
			valid = true;
		return valid;
	}
	bool Date::operator!=(const Date& rhs)const {
		bool valid = true;
		if (*this == rhs)
			valid = false;
		return valid;
	}
	bool Date::operator<(const Date& rhs)const {
		bool valid = false;
		if (year < rhs.year) {
			valid = true;
		}
		else if (year == rhs.year) {
			if (month < rhs.month) {
				valid = true;
			}
			else if (month == rhs.month) {
				if (day < rhs.day) {
					valid = true;
				}
			}
		}
		if (year == rhs.year && month == rhs.month && day == rhs.day) {
			valid = false;
		}
		return valid;
	}
	bool Date::operator>(const Date& rhs)const {
		bool valid = true;
		if (*this < rhs || *this == rhs)
			valid = false;
		return valid;
	}
	bool Date::operator<=(const Date& rhs)const {
		bool valid = false;
		if (*this < rhs || *this == rhs)
			valid = true;
		return valid;
	}
	bool Date::operator>=(const Date& rhs)const {
		bool valid = false;
		if (*this > rhs || *this == rhs)
			valid = true;
		return valid;
	}
	istream& Date::read(istream& is) {
		int year_n, month_n, day_n;
		bool valid = true;
		is >> year_n;
		if (is.fail())
			valid = false;
		is.ignore();
		is >> month_n;
		if (is.fail())
			valid = false;
		is.ignore();
		is >> day_n;
		//is.ignore();
		if (is.fail())
			valid = false;
		Date tmp = Date(year_n, month_n, day_n);
		*this = tmp;
		if (valid == false) {
			*this = Date();
			currentStatus = error_input;
		}
		return is;
	}
	ostream& Date::write(ostream& os) const {
		os.setf(ios::right);
		os.fill('0');
		os.width(4);
		os << year << "/";
		os.width(2);
		os << month << "/";
		os.width(2);
		os << day;
		os.fill(' ');
		os.unsetf(ios::right);
		return os;
	}
	ostream& operator<<(ostream& os, const Date& rhs) {
		rhs.write(os);
		return os;
	}
	istream& operator>>(istream& is, Date& rhs) {
		rhs.read(is);
		return is;
	}
}
