#include <iostream>
#include <fstream>
#include <iomanip>
#include<cmath>
using namespace std;

typedef struct
{
    string name;
	string class_name;
	int stream;
	int main_subject_marks;
    int physics_marks;
	int chemistry_marks;
	int class_rank;
	int school_rank;
	int total_marks;
	double z_score;
}
student;

student STUDENTS[500];
int student_count = 0;

void print_rankings(int no_of_students);
void write_data_to_file(int student_count);
void sort_students(int no_of_students);
void z_score(int no_of_students);

int main(void) {

	int option;

	while (true)
	{
		cout << "--------------------------\n";
		cout << "------ A/L Rankings ------\n";
		cout << "--------------------------\n";
		cout << "1) Add Students and Marks\n";
		cout << "2) See Rankings\n";
		cout << "3) Write Marks to a file\n";

		// Taking input for the option
		cout << "Choose an option\n";
		cin >> option;

		// Error Checking on the selected option
		if (option != 1 && option != 2 && option != 3) {
			cout << "Choose correct option\n";
			// cout << "Press Enter to Continue\n\n\n";
			continue;
		}

		// Adding students
		int no_of_students;
		if (option == 1) {
			cout << "\nEnter No of students adding: ";
			cin >> no_of_students;
			cout << no_of_students << endl;
		} else if (option == 2) {
			print_rankings(student_count);
			continue;
		} else {
			write_data_to_file(student_count);
			cout << "Data Written to file\n";
			break;
		}

		// Taking student data to an array of students
		student students[no_of_students];
		for (int i = 0; i < no_of_students; i++) {
			student temp;
			cout << "-----------------------\n";
			
			cout << "Name: ";
			cin.ignore();
			getline(cin, temp.name);

			while (true) {
				cout << "Select Stream\n";
				cout << "1) Bio\n";
				cout << "2) Math\n";
				cout << "Stream No: ";
				cin >> temp.stream;

				if (temp.stream == 1) {
					cout << "Bio Marks: ";
				} else if (temp.stream == 2) {
					cout << "Math Marks: ";
				} else {
					cout << "Choose correct option\n";
					continue;
				}
				cin.ignore();
				cin >> temp.main_subject_marks;
				break;
			}

			cout << "Physics Marks: ";
			cin.ignore();
			cin >> temp.physics_marks;

			cout << "Chemistry Marks: ";
			cin.ignore();
			cin >> temp.chemistry_marks;

			while (true) {
				int class_no;
				cout << "Choose Class No\n";
				if (temp.stream == 1) {
					cout << "1) 12A\n";
					cout << "2) 12B\n";
					cout << "3) 12C\n";
				} else {
					cout << "1) 12D\n";
					cout << "2) 12E\n";
					cout << "3) 12F\n";
					cout << "4) 12G\n";
					cout << "5) 12H\n";
				}

				cout << "Class No: ";
				cin.ignore();
				cin >> class_no;

				if (temp.stream == 1 && (class_no < 1 || class_no > 3)) {
					cout << "Choose correct option\n";
					continue;
				} else if (class_no < 1 || class_no > 5) {
					cout << "Choose correct option\n";
					continue;
				}

				if (temp.stream == 1) {
					switch (class_no)
					{
						case 1:
							temp.class_name = "12A";
							break;
						case 2:
							temp.class_name = "12B";
							break;
						case 3:
							temp.class_name = "12C";
							break;
					}
				} 
				else if (temp.stream == 2) {
					switch (class_no)
					{
						case 1:
							temp.class_name = "12D";
							break;
						case 2:
							temp.class_name = "12E";
							break;
						case 3:
							temp.class_name = "12F";
							break;
						case 4:
							temp.class_name = "12G";
							break;
						case 5:
							temp.class_name = "12H";
							break;
					}
				}

				break;
			}

			// Calculating the total score
			temp.total_marks = temp.main_subject_marks + temp.chemistry_marks + temp.physics_marks;
			STUDENTS[student_count] = temp;
			student_count++;
		}

		// Sorting the students
		sort_students(student_count);

		// School Ranking
		for (int i = student_count; i >= 0; i--) {
			STUDENTS[i].school_rank = i+1;
		}

		// Class Ranking
		int C_12A = 1, C_12B = 1, C_12C = 1, C_12D = 1, C_12E = 1, C_12F = 1, C_12G = 1, C_12H = 1;
		for (int i = 0; i < student_count; i++) {
			if (STUDENTS[i].class_name == "12A") {
				STUDENTS[i].class_rank = C_12A;
				C_12A++;
			} else if (STUDENTS[i].class_name == "12B") {
				STUDENTS[i].class_rank = C_12B;
				C_12B++;
			} else if (STUDENTS[i].class_name == "12C") {
				STUDENTS[i].class_rank = C_12C;
				C_12C++;
			} else if (STUDENTS[i].class_name == "12D") {
				STUDENTS[i].class_rank = C_12D;
				C_12D++;
			} else if (STUDENTS[i].class_name == "12E") {
				STUDENTS[i].class_rank = C_12E;
				C_12E++;
			} else if (STUDENTS[i].class_name == "12F") {
				STUDENTS[i].class_rank = C_12F;
				C_12F++;
			} else if (STUDENTS[i].class_name == "12G") {
				STUDENTS[i].class_rank = C_12G;
				C_12G++;
			} else if (STUDENTS[i].class_name == "12H") {
				STUDENTS[i].class_rank = C_12H;
				C_12H++;
			} 
		}

		// Calculating the z-score
		z_score(student_count);
		
		// Printing the rankings
		print_rankings(student_count);
	}
}

void sort_students(int no_of_students) {
	// Sorting the students according to their total marks
	// Using insertion sort
	for (int i = 1; i < no_of_students; i++)
	{
		student k = STUDENTS[i];
		int key = STUDENTS[i].total_marks;
		int j = i - 1;

		while (j >= 0 && STUDENTS[j].total_marks < key)
		{
			STUDENTS[j + 1] = STUDENTS[j];
			j = j - 1;
		}
		STUDENTS[j + 1] = k;
	}
}

void write_data_to_file(int student_count) {
	ofstream File;
	File.open("ranking.txt");

	File << "A/L Rankings\n\n";
	
	// Math Students
	File << "Math Students\n" << endl;
	File << left << setw(18) << "Name" << setw(18) << "Class Name"  << setw(18) << "Total Marks" << setw(18) << "School Rank" << setw(18) << "Class Rank" << setw(18) << "Z-Score" << endl;
	for (int i = 0; i < student_count; i++) {
		if (STUDENTS[i].name != "" && STUDENTS[i].stream == 2)
			File << left << setw(18) << STUDENTS[i].name << setw(18) << STUDENTS[i].class_name << setw(18) << STUDENTS[i].total_marks << setw(18) << STUDENTS[i].school_rank << setw(18) << STUDENTS[i].class_rank << setw(18) << STUDENTS[i].z_score << endl;
	}

	// Bio Students
	File << "\n\n\nBioscience Students\n" << endl;
	File << left << setw(18) << "Name" << setw(18) << "Class Name"  << setw(18) << "Total Marks" << setw(18) << "School Rank" << setw(18) << "Class Rank" << setw(18) << "Z-Score" << endl;
	for (int i = 0; i < student_count; i++) {
		if (STUDENTS[i].name != "" && STUDENTS[i].stream == 1)
			File << left << setw(18) << STUDENTS[i].name << setw(18) << STUDENTS[i].class_name << setw(18) << STUDENTS[i].total_marks << setw(18) << STUDENTS[i].school_rank << setw(18) << STUDENTS[i].class_rank << setw(18) << STUDENTS[i].z_score << endl;
	}

	File.close();
}

void print_rankings(int no_of_students) {
	// Printing the rankings and students
	cout << "\n";
	cout << left << setw(18) << "Name" << setw(18) << "Stream" << setw(18) << "Class Name" << setw(18) << "Total Marks" << setw(18) << "School Rank" << setw(18) << "Class Rank" << setw(18) << "Z-Score" << endl;
	
	for (int i = 0; i < no_of_students; i++) {
		if (STUDENTS[i].name != "")
		{
			string stream;
			if (STUDENTS[i].stream == 1) {
				stream = "Bio";
			} else {
				stream = "Math";
			}
			cout << left << setw(18) << STUDENTS[i].name << setw(18) << stream << setw(18) << STUDENTS[i].class_name << setw(18) << STUDENTS[i].total_marks << setw(18) << STUDENTS[i].school_rank << setw(18) << STUDENTS[i].class_rank << setw(18) << STUDENTS[i].z_score << endl;
		}
	}
}

void z_score(int no_of_students) {
	// Calculating the Z-Score
	// Reference - https://www.wikihow.com/Calculate-Z-Scores

	// If there is only one element
	if (no_of_students == 1) {
		STUDENTS[0].z_score = 0;
		return;
	}

	// Calculating the mean
	double mean;
	double sum = 0;
	for (int i = 0; i < no_of_students; i++) {
		sum += STUDENTS[i].total_marks;
	}
	mean = sum / no_of_students;

	// Finding the variance
	double variance = 0;
	sum = 0;
	for (int i = 0; i < no_of_students; i++) {
		 sum += pow(STUDENTS[i].total_marks - mean, 2);
	}
	variance = sum / (double) no_of_students-1;

	// Calculating the Standard Deviation
	double deviation = sqrt(variance);

	// Calculating Z Scores
	for (int i = 0; i < no_of_students; i++) {
		STUDENTS[i].z_score = (STUDENTS[i].total_marks - mean) / deviation;
	}
}