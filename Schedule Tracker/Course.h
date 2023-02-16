#ifndef COURSE_H_
#define COURSE_H_

#include <string>
#include <ostream>
#include <sstream>
#include <iostream>

using namespace std;

class Course {
protected:
	string courseName;
public:
	Course(string course) : courseName(course) {}

	friend ostream& operator<<(ostream& os, const Course& course) {
		os << course.toString();
		return os;
	}

	virtual string toString() const {
		ostringstream oss;
		oss << "Name = " << courseName;
		return oss.str();
	}
};
#endif

