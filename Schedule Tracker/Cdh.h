#ifndef CDH_H_
#define CDH_H_

#include "Course.h"

class Cdh :  public Course {
protected:
	string day;
	string time;
public:
	Cdh(string name, string day, string time) : day(day), time(time), Course(name) {}

	friend ostream& operator<<(ostream& os, const Cdh& course) {
		os << course.toString();
		return os;
	}

	string getDay() {
		return day;
	}

	string getTime() {
		return time;
	}

	string getCourse() {
		return courseName;
	}

	string toString() const {
		ostringstream oss;
		oss << "cdh(" << courseName << "," << day << "," << time << ")";
		return oss.str();
	}
};
#endif