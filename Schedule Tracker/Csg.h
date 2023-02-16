#ifndef CSG_H_
#define CSG_H_

#include "Course.h"

class Csg : public Course {
protected:
	string studentID;
	string grade;
public:
	Csg(string name, string id, string grade) : studentID(id), grade(grade), Course(name) {}

	friend ostream& operator<<(ostream& os, const Csg& course) {
		os << course.toString();
		return os;
	}

	string getID() {
		return studentID;
	}

	string getGrade() {
		return grade;
	}

	string getCourse() {
		return courseName;
	}

	string toString() const {
		ostringstream oss;
		oss << "csg(" << courseName << "," << studentID << "," << grade << ")";
		return oss.str();
	}
};
#endif

