#define _CRT_SECURE_NO_WARNINGS
// Milestone:	2
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		ErrorState.cpp

#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace ama {
	ErrorState::ErrorState(const char* errorMessage) {
		currentMessage = errorMessage;
		if (*this) {
			currentMessage = nullptr;
		}
		else {
			currentMessage = new const char[strlen(errorMessage)];
			strncpy((char*)currentMessage, errorMessage, strlen(errorMessage));
		}
	}
	ErrorState::~ErrorState() {
		delete[] currentMessage;
		currentMessage = nullptr;
	}
	ErrorState::operator bool() const {
		bool check = false;
		if (currentMessage == nullptr || currentMessage[0] == '\0')
			check = true;
		return check;
	}
	ErrorState& ErrorState::operator=(const char * pText) {
		ErrorState temp(pText);
		if (!temp) {
			delete[] currentMessage;
			this->currentMessage = temp.currentMessage;
			temp.currentMessage = nullptr;
		}
		return *this;
	}
	void ErrorState::message(const char * pText) {
		*this = pText;
	}
	const char * ErrorState::message() const {
		return currentMessage;
	}
	/*ostream& ErrorState::write(ostream& os) const {
		if (!*this)
			os << currentMessage;
		return os;
	}*/
	ostream& operator<<(ostream& os,const ErrorState& rhs) {
		const char* msg = rhs.message();
		if(msg)
		os << msg;
		return os;
	}
}
