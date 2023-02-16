#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

string calcScore(int score, float avg) {
	if (abs((score - avg)) <= 5.0) {
		return "(C)";
	}
	else if (((score - avg) < 15.0) && ((score - avg) > 5)) {
		return "(B)";
	}
	else if (((score - avg) > -15.0) && ((score - avg) < -5)) {
		return "(D)";
	}
	else if (((score - avg) >= 15.0)) {
		return "(A)";
	}
	else if (((score - avg) <= -15.0)) {
		return "(E)";
	}
	else {
		return "ERROR";
	}
}

string calcScore(float score, float avg) {
	if (abs((score - avg)) <= 5.0) {
		return "(C)";
	}
	else if (((score - avg) < 15.0) && ((score - avg) > 5)) {
		return "(B)";
	}
	else if (((score - avg) > -15.0) && ((score - avg) < -5)) {
		return "(D)";
	}
	else if (((score - avg) >= 15.0)) {
		return "(A)";
	}
	else if (((score - avg) <= -15.0)) {
		return "(E)";
	}
	else {
		return "ERROR";
	}
}

int main(int argc, char* argv[]) {
	VS_MEM_CHECK
	//initalize io
	if (argc < 3) {
		cerr << "Please provide name of input and output files";
		return 1;
	}

	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}

	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	//declare dynamic array s
	int rows = 1;
	int cols = 1;
	in >> rows;
	in >> cols;

	int** myArray = new int* [rows];
	for (int i = 0; i < rows; i++)  {
		myArray[i] = new int[cols];
	}

	string* students = new string[rows];
	for (int i = 0; i < rows; i++) {
		students[i] = "null";
	}

	//initalize dynamic arrays
	in.ignore(numeric_limits<int>::max(), '\n');
	string line;
	for (int i = 0; i < rows; i++) {
		getline(in, line);
		size_t p = 0;
		while (!isdigit(line[p])) ++p;
		students[i] = line.substr(0, p-1);

		p = 0;
		while (!isdigit(line[p])) ++p;
		line = line.substr(p);
		istringstream iss(line);

		for (int j = 0; j < cols; j++) {
			
			iss >> myArray[i][j];
		}
	}

	//output to file
	
	//student scores
	out << "Student Scores:" << endl;
	for (int i = 0; i < rows; i++) {
		out << setw(20) << students[i] << " ";
		for (int j = 0; j < cols; j++) {
			out << fixed << setprecision(0) << setw(6);
			out << myArray[i][j];
		}
		out << endl;
	}

	//exam averages
	out << "Exam Averages:" << endl;
	float* avgs = new float[cols];
	float avg = 0;
	for (int j = 0; j < cols; j++) {
		for (int i = 0; i < rows; i++) {
			avg += myArray[i][j];
		}
		avg = (avg + 0.0) / rows;
		avgs[j] = avg;
		avg = 0;
	}
	for (int j = 0; j < cols; j++) {
		out << setw(20);
		out << "Exam " << j+1 << " Average = " << " ";
		out << fixed << setprecision(1) << setw(6);
		out << avgs[j] << endl;
	}

	//student exam grades
	out << "Student Exam Grades:" << endl;
	for (int i = 0; i < rows; i++) {
		out << setw(20) << students[i] << " ";
		for (int j = 0; j < cols; j++) {
			out << fixed << setprecision(0) << setw(6);
			out << myArray[i][j] << calcScore(myArray[i][j],avgs[j]);
		}
		out << endl;
	}
	//exam grades
	int** scores = new int* [cols];
	for (int i = 0; i < cols; i++) {
		scores[i] = new int[5];
	}

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < 5; j++) {
			scores[i][j] = 0;
		}
	}

	string temp = "";
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			temp = calcScore(myArray[j][i], avgs[i]);
			if (temp == "(A)") {
				scores[i][0]++;
			}
			if (temp == "(B)") {
				scores[i][1]++;
			}
			if (temp == "(C)") {
				scores[i][2]++;
			}
			if (temp == "(D)") {
				scores[i][3]++;
			}
			if (temp == "(E)") {
				scores[i][4]++;
			}
		}
	}
	out << "Exam Grades:" << endl;
	for (int i = 0; i < cols; i++) {
		out << setw(10);
		out << "Exam " << i+1 << " ";
		for (int j = 0; j < 5; j++) {
			switch (j) {
			case 0:
				temp = "(A)";
				break;
			case 1:
				temp = "(B)";
				break;
			case 2:
				temp = "(C)";
				break;
			case 3:
				temp = "(D)";
				break;
			case 4:
				temp = "(E)";
				break;
			default:
				temp = "ERROR";
				break;
			}
			out << fixed << setprecision(1) << setw(6);
			out << scores[i][j] << temp;
		}
		out << endl;
	}

	//student final grades
	out << "Student Final Grades:" << endl;
		//calc avg class score
	avg = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			avg += myArray[i][j];
		}
	}
	avg = (avg + 0.0) / (rows * cols);

	float tempAverage = 0;;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tempAverage += myArray[i][j];
		}
		tempAverage = (tempAverage + 0.0) / cols;
		out << setw(20) << students[i] << " ";
		out << fixed << setprecision(1) << setw(6);
		out << tempAverage << calcScore(tempAverage, avg) << endl;
		tempAverage = 0;
	}

	//class average score
	
	out << "Class Average Score = " << avg << endl;

	//memory clear
	for (int i = 0; i < rows; i++) {
		delete [] myArray[i];
	}
	for (int i = 0; i < cols; i++) {
		delete[] scores[i];
	}
	delete[] myArray;
	delete[] scores;
	delete[] students;
	delete[] avgs;

	return 0;
}