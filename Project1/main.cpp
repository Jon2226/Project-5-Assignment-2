// CSCN73030-F24: Project 5 - Assignment 2
// Jonathan Ward

// Read student data from files and store in vector

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define NAMES_FILE		"StudentData.txt"
#define EMAILS_FILE		"StudentData_Emails.txt"

struct STUDENT_DATA {
	string first_name;
	string last_name;
};

// Remove leading or trailing whitespace from a string
string trim(const string& str) {
	size_t first = str.find_first_not_of(" \t\n\r\f\v");	// Find index of first non-whitespace
	if (first == string::npos) return "";					// If all whitespace, return empty
	size_t last = str.find_last_not_of(" \t\n\r\f\v");		// Find index of last non-whitespace
	return str.substr(first, (last - first + 1));			// return string between those indices
}

vector<STUDENT_DATA> read_names(string file_name) {
	ifstream input_file(file_name);
	string line = "";
	vector<STUDENT_DATA> all_students;

	if (!input_file) {
		cerr << "Unable to open file " << file_name << endl;
		return all_students;
	}
	else
	{
		while (getline(input_file, line)) {
			istringstream ss(line);
			STUDENT_DATA student;
			if (getline(ss, student.last_name, ',') && getline(ss, student.first_name)) {
				// Remove any leading or trailing whitespace from each name
				student.last_name = trim(student.last_name);
				student.first_name = trim(student.first_name);
				all_students.push_back(student);
			}
		}
	}
	input_file.close();
	return all_students;
};

int main() {
	vector<STUDENT_DATA> all_students = read_names(NAMES_FILE);

	return 1;
}

