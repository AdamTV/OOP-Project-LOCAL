// Milestone:	5
// Name:		ADAM STINZIANI
// Student #:	124521188
// Course:		OOP244 Winter 2019
// File:		ErrorState.h
#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H
#include<iostream>

namespace ama {
	class ErrorState {
		char * currentMessage;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		virtual ~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char * pText);
		void message(const char * pText);
		const char * message() const;
	};
	std::ostream& operator<<(std::ostream&, const ErrorState&);
}


#endif