#include "stdafx.h"
#include "events.h"

class Subject {  // Printer
public:
	// void(Subject *sender)
	event<Subject> onDataChanged;
	// void(Subject *sender, int age)
	event<Subject, int> onNewAgeReceived;
	// void(Subject *sender, int oldAge, int newAge)
	event<Subject, int, int> onAgeChanged;

	// need to pass the sender param when constructing the events
	Subject() : onDataChanged(this), onNewAgeReceived(this), onAgeChanged(this) {}

	void updateAge(int newAge) {
		int oldAge = age;
		age = newAge;
		// sender, aka this will be automatically passed to the subscribers
		// the () operator is protected, however Subject is friend to event
		// trying to raise the event from outside the class is not possible
		onDataChanged();
		onNewAgeReceived(age);
		onAgeChanged(oldAge, newAge);
	}
	void NewYearComing(int year) {
		this->age = year - 1987;
		onNewAgeReceived(this->age);
	}
private:
	int age;
};
// OT => Object Type
// RT => Return Type
// A ... => Arguments
template<typename OT, typename RT, typename ... A>
struct lambda_expression {
	OT _object;
	RT(OT::*_function)(A...)const;

	lambda_expression(const OT & object)
		: _object(object), _function(&decltype(_object)::operator()) {}

	RT operator() (A ... args) const {
		return (_object.*_function)(args...);
	}
};
auto noncapture_lambda() {
	auto lambda = [](Subject *sender, int age) {
		printf("do whatever is needed 111111\n");
	};
	return lambda_expression<decltype(lambda), void, Subject*, int>(lambda);
}

class Observer {  // CefV8Handler
private:
	Subject *subject;
public:
	Observer(Subject *aSubject) : subject(aSubject) {
		// instance methods need to use the event_handler() helper function
		subject->onDataChanged += event_handler(this, &Observer::subjectChanged);

		// static class methods, or global ones can also be added
		subject->onAgeChanged += &Observer::subjectAgeChanged;

		// can also add lambdas (however those can't be removed)
		subject->onNewAgeReceived += [=](Subject *sender, int age) {
			printf("Subject received new age: %d\n", age);
		};

		//// non-capturing lamdba's need a workardound otherwise the compiler will
		//// complain about += being ambigous, calling the unary "+" operator will do the trick
		//subject->onNewAgeReceived += +[](Subject *sender, int age) {
		//	// do whatever is needed
		//};
		subject->onNewAgeReceived += [this](Subject *sender, int age) {  // ok ÍÆ¼ö£¿
			// do whatever is needed
			printf("do whatever is needed 33333333\n");
		};

		//std::function<int(void)>  //std::function<returnType(args...)>
		std::function<void(Subject*, int)> t = [](Subject *sender, int age) {
			// do whatever is needed
			printf("do whatever is needed 4444\n");
		};
		subject->onNewAgeReceived += t;  // ok

		subject->onNewAgeReceived += (std::function<void(Subject*, int)>)[](Subject *sender, int age) {  // ok ÍÆ¼ö£¿
			// do whatever is needed
			printf("do whatever is needed 55555\n");
		};

		//auto f_noncapture = noncapture_lambda();
		subject->onNewAgeReceived += noncapture_lambda();  // ok
		subject->onNewAgeReceived += ([]() {  // ok
			auto lambda = [](Subject *sender, int age) {
				printf("do whatever is needed 222222\n");
			};
			return lambda_expression<decltype(lambda), void, Subject*, int>(lambda); 
		})();
	}

	virtual ~Observer() {
		// remove the attached event handlers
		subject->onDataChanged -= event_handler(this, &Observer::subjectChanged);
		subject->onAgeChanged -= &Observer::subjectAgeChanged;
	}

	void subjectChanged(Subject *sender) {
		printf("Subject changed\n");
	}

	static void subjectAgeChanged(Subject *sender, int oldAge, int newAge) {
		printf("Subject age changed from %d to %d\n", oldAge, newAge);
	}
};