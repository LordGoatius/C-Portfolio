#ifndef SNAP_H_
#define SNAP_H_

#include<string>
#include<iostream>
#include<iomanip>
#include <sstream>

using namespace std;

class Snap {
private:
	string studentID;
	string studentName;
	string studentAddress;
	string studentNumber;
public:
	Snap(string id, string studentName, string studentAddress, string studentNumber) : 
		studentAddress(studentAddress), studentID(id), studentName(studentName), studentNumber(studentNumber) {}

	friend ostream& operator<<(ostream& os, const Snap& course) {
		os << course.toString();
		return os;
	}

	string getID() {
		return studentID;
	}

	string getName() {
		return studentName;
	}

	string getAddress() {
		return studentAddress;
	}

	string getNumber() {
		return studentNumber;
	}

	string toString() const {
		ostringstream oss;
		oss << "snap(" << studentID << "," << studentName << "," << studentAddress << "," << studentNumber << ")";
		return oss.str();
	}
};
#endif