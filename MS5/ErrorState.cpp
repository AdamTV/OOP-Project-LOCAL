#define _CRT_SECURE_NO_WARNINGS
// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		ErrorState.cpp

#include <cstring>
#include "ErrorState.h"

using namespace std;

namespace ama {
	ErrorState::ErrorState(const char* errorMessage) {
		currentMessage = nullptr;
		if (errorMessage != nullptr && errorMessage[0] != '\0') {
			currentMessage = new char[strlen(errorMessage) + 1];
			strncpy(currentMessage, errorMessage, strlen(errorMessage));
			currentMessage[strlen(errorMessage)] = '\0';
		}
		else {
			currentMessage = nullptr;
		}
	}
	ErrorState::~ErrorState() {
		if(currentMessage != nullptr){
		delete[] currentMessage;
		currentMessage = nullptr;
		}
	}
	ErrorState::operator bool() const {
		bool check = true;
		if (currentMessage == nullptr)
			check = false;
		return check;
	}
	ErrorState& ErrorState::operator=(const char * pText) {
		ErrorState temp(pText);
		if (temp) {
			delete[] currentMessage;
			currentMessage = nullptr;
			this->currentMessage = temp.currentMessage;
			temp.currentMessage = nullptr;
		}
		else {
			currentMessage = nullptr;
		}
		return *this;
	}
	void ErrorState::message(const char * pText) {
		*this = pText;
	}
	const char * ErrorState::message() const {
		return currentMessage;
	}
	ostream& operator<<(ostream& os, const ErrorState& rhs) {
		const char* msg = rhs.message();
		if (msg)
			os << msg;
		return os;
	}
}
