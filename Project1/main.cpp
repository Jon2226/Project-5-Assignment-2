// CSCN73030-F24: Project 5 - Assignment 2
// Jonathan Ward

// Read student data from plaintext files and store in vector

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define NAMES_FILE		"StudentData.txt"
#define EMAILS_FILE		"StudentData_Emails.txt"

#define PRE_RELEASE

struct STUDENT_DATA {
	string first_name;
	string last_name;
	string email;
};

// Remove leading or trailing whitespace from a string
string trim(const string& str) {
	size_t first = str.find_first_not_of(" \t\n\r\f\v");	// Find index of first non-whitespace
	if (first == string::npos) return "";					// If all whitespace, return empty
	size_t last = str.find_last_not_of(" \t\n\r\f\v");		// Find index of last non-whitespace
	return str.substr(first, (last - first + 1));			// return string between those indices
}

// Each line should resemble this CSV format:
// Lastname, Firstname, email@domain.com
// However, email may or may not be present.
STUDENT_DATA read_line(string line) {
	STUDENT_DATA student;
	istringstream ss(line);
	string token;
	vector<string> tokens;

	while (getline(ss, token, ',')) {
		tokens.push_back(trim(token));
	}

	// Only assign email if the correct number of string tokens are present
	if (tokens.size() > 0)
		student.last_name = tokens[0];
	if (tokens.size() > 1)
		student.first_name = tokens[1];
	if (tokens.size() > 2)
		student.email = tokens[2];

	return student;
}

// Read student names from given plaintext data file into a vector
vector<STUDENT_DATA> read_student_data(string file_name) {
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
			STUDENT_DATA student = read_line(line);
			all_students.push_back(student);
		}
	}
	input_file.close();
	return all_students;
};

int main() {
	cout << "Running pre-release version" << endl;

#ifdef PRE_RELEASE
	vector<STUDENT_DATA> all_students = read_student_data(EMAILS_FILE);
 #else
	vector<STUDENT_DATA> all_students = read_student_data(NAMES_FILE);
 #endif

// Using NDEBUG because it's standardized for C/C++ (doesn't specifically depend on Visual Studio).
// See: https://github.com/microsoft/qsharp-runtime/issues/600
#if !defined(NDEBUG)
	// DEBUG: print all student information to stdout
	for (const auto& student : all_students) {
		cout << "Last name: " << student.last_name << endl;
		cout << "First name: " << student.first_name << endl;
		cout << "Email: " << student.email << endl;
		cout << endl;
	}
#endif

	return 1;
}

