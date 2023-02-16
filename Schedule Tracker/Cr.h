#ifndef CR_H_
#define CR_H_

#include "Course.h"

class Cr : public Course {
protected:
	string room;
public:
	Cr(string course, string room) : Course(course), room(room) {}

	friend ostream& operator<<(ostream& os, const Cr& course) {
		os << course.toString();
		return os;
	}

	string getCourse() {
		return courseName;
	}

	string getRoom() {
		return room;
	}

	string toString() const {
		ostringstream oss;
		oss << "cr(" << courseName << "," << room << ")";
		return oss.str();
	}
};
#endif