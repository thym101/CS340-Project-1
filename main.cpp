#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    string firstName;
    string lastName;
    string phoneNumber; 
};

struct Course {
    string courseName;
};

unordered_map<int, Student> studentInfo;
unordered_map<string, Course> courseInfo;
unordered_map<int, unordered_map<string, string> > grades;


void readStudents(const string& filename);
void readCourses(const string& filename);
void readGrades(const string& filename);
void menu();
void modifyGrade ();
void removeGrade(int studentId, const string& courseNumber);
void studentGradeReport(const string& studentIdInput);
void courseGradeReport(const string& courseNum);
void listStudents();
void displayCourseListing();
void saveAndExit();

int main()
{
    readStudents("student.dat");
    readCourses("course.dat");
    readGrades("grade.dat");
    
    int choice = 0;
    
    while (choice != 7) {
        menu();
        cin >> choice;

        switch (choice) {
            case 1:
                modifyGrade();
                break;
            case 2: {
                int studentId;
                string courseNumber;
                cout << "Enter Student ID: ";
                cin >> studentId;
                cout << "Enter Course Number: ";
                cin >> courseNumber;
                removeGrade(studentId, courseNumber);
                break;
            }
            case 3: {
                string studentIdInput;
                cout << "Enter Student ID (* for all students): ";
                cin >> studentIdInput;
                studentGradeReport(studentIdInput);
                break;
            }
            case 4: {
                string courseNumber;
                cout << "Enter Course Number (* for all courses): ";
                cin >> courseNumber;
                courseGradeReport(courseNumber);
                break;
            }
            case 5:
                listStudents();
                break;
            case 6:
                displayCourseListing();
                break;
            case 7:
                saveAndExit();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void readStudents(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }

    //Skip first line
    string header;
    getline(file, header); 

    int id;
    Student student;
    while (file >> student.firstName >> student.lastName >> id >> student.phoneNumber) {
        studentInfo[id] = student;
    }

    file.close();
}

void readCourses(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string header;
    getline(file, header); 

    string courseNumber;
    Course course;
    while (file >> courseNumber >> course.courseName) {
        courseInfo[courseNumber] = course;
    }

    file.close();
}

void readGrades(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string header;
    getline(file, header); 

    int studentId;
    string courseNumber;
    string grade;
    while (file >> studentId >> courseNumber >> grade) {
        grades[studentId][courseNumber] = grade;
    }

    file.close();
}  
void menu() {
    cout << "1. Add/modify a grade" << endl;
    cout << "2. Remove a grade" << endl;
    cout << "3. Student grade report" << endl;
    cout << "4. Course grade report" << endl;
    cout << "5. List students" << endl;
    cout << "6. Display course listing" << endl;
    cout << "7. Exit" << endl;
    cout << endl << "Enter your choice: "<< endl;

}

//1. Add/change a grade 
void modifyGrade () {
    int studentID;
    string courseNum, grade;

    cout << "Enter Student ID: ";
    cin >> studentID;
    if (studentInfo.find(studentID) == studentInfo.end()) {
        cout << "Student ID " << studentID << " does not exist in the system." << endl;
        return;
    }

    cout << "Enter Course Number: ";
    cin >> courseNum;
    if (courseInfo.find(courseNum) == courseInfo.end()) {
        cout << "Course Number " << courseNum << " does not exist in the system." << endl;
        return;
    }

    cout << "Enter Grade (A, B, C, D, F, I) or Q to quit: ";
    cin >> grade;
    if (grade == "Q" || grade == "q") {
        cout << "Operation canceled." << endl;
        return;
    }
    if (grade != "A" && grade != "B" && grade != "C" && grade != "D" && grade != "F" && grade != "I") {
        cout << "Invalid grade. Please enter one of the following: A, B, C, D, F, I." << endl;
        return;
    }

    if (grades[studentID].find(courseNum) != grades[studentID].end()) {
        grades[studentID][courseNum] = grade; // Update existing grade
        cout << "Success: Grade updated for Student ID " << studentID << " in course " << courseNum << "." << endl;
    } else {
        grades[studentID][courseNum] = grade; // Add new grade
        cout << "Success: Grade added for Student ID " << studentID << " in course " << courseNum << "." << endl;
    }
}

//2. Remove a grade
void removeGrade(int studentId, const string& courseNumber) {
    if (studentInfo.find(studentId) == studentInfo.end()) {
        cout << "Student ID " << studentId << " does not exist." << endl;
        return;
    }

    if (grades.find(studentId) == grades.end()) {
        cout << "Student ID " << studentId << " does not exist." << endl;
        return;
    }

    auto& studentGrades = grades[studentId];

    if (studentGrades.find(courseNumber) == studentGrades.end()) {
        cout << "Grade for course " << courseNumber << " does not exist for Student " << studentId << "." << endl;
        return;
    }

    
    studentGrades.erase(courseNumber);
    cout << "Grade for course " << courseNumber << " has been removed for student " << studentId << "." << endl;

    if (studentGrades.empty()) {
        grades.erase(studentId);
        studentInfo.erase(studentId);
        cout << "Note: Student ID " << studentId << " has been removed from the system." << endl;
    }
}

//3. Student grade report
void studentGradeReport(const string& studentIdInput) {
    if (studentIdInput == "*") {
        cout << setw(15) << "Firstname";
        cout << setw(15) << "Lastname";
        cout << setw(15) << "ID";
        cout << setw(20) << "Course";
        cout << setw(15) << "Course Number";
        cout << setw(15) << "Grade" << endl;

        for (const auto& studentPair : grades) {
            int studentID = studentPair.first;

            if (studentInfo.find(studentID) == studentInfo.end()) {
                cout << "Student ID " << studentID << " not found in studentInfo." << endl;
                continue;
            }

            const auto& student = studentInfo.at(studentID);
            const auto& courseGrades = studentPair.second;

            for (const auto& gradePair : courseGrades) {
                const string& courseNumber = gradePair.first;

                if (courseInfo.find(courseNumber) == courseInfo.end()) {
                    cout << "Course number " << courseNumber << " not found in courseInfo." << endl;
                    continue;
                }

                const auto& course = courseInfo.at(courseNumber);
                const string& grade = gradePair.second;

                cout << setw(15) << student.firstName 
                     << setw(15) << student.lastName 
                     << setw(15)<< studentID 
                     << setw(20) << course.courseName 
                     << setw(15) << courseNumber 
                     << setw(15) << grade << endl;
            }
        }
    } else {
        int studentId = stoi(studentIdInput);

        if (grades.find(studentId) == grades.end()) {
            cout << "Error: Student ID " << studentId << " not found in grades." << endl;
            return;
        }

        if (studentInfo.find(studentId) == studentInfo.end()) {
            cout << "Error: Student ID " << studentId << " not found in studentInfo." << endl;
            return;
        }

        const auto& courseGrades = grades.at(studentId);
        const auto& student = studentInfo.at(studentId);

        cout << "Grade Report for Student ID: " << studentId << endl;
        cout << setw(15) << "Course Name"
             << setw(20) << "Course Number"
             << setw(15) << "Grade" << endl;

        for (const auto& gradePair : courseGrades) {
            const string& courseNumber = gradePair.first;

            if (courseInfo.find(courseNumber) == courseInfo.end()) {
                cout << "Error: Course number " << courseNumber << " not found in courseInfo." << endl;
                continue;
            }

            const auto& course = courseInfo.at(courseNumber);
            const string& grade = gradePair.second;

            cout << setw(15) << course.courseName
                 << setw(20) << courseNumber
                 << setw(15) << grade << endl;
            
        }
    }
}

//4. Course grade report
void courseGradeReport (const string& courseNum) {
    if(courseNum == "*") {
        cout << setw(15) << "Firstname";
        cout << setw(15) << "Lastname";
        cout << setw(15) << "ID";
        cout << setw(20) << "Course";
        cout << setw(15) << "Course Number";
        cout << setw(15) << "Grade" << endl;

        for (const auto& studentPair : grades) {
            int studentID = studentPair.first;
            const auto& courseGrades = studentPair.second;
            const auto& student = studentInfo.at(studentID);

            for(const auto& gradePair : courseGrades) {
                const string& courseNumber = gradePair.first;
                const string& grade = gradePair.second;
                const auto& course = courseInfo.at(courseNumber);

                cout << setw(15) << student.firstName 
                     << setw(15) << student.lastName 
                     << setw(15)<< studentID 
                     << setw(20) << course.courseName 
                     << setw(15) << courseNumber 
                     << setw(15) << grade << endl;
            }
        }
    } else {
        cout << "Course report for: " << courseNum << endl;
        cout << setw(15) << "Firstname";
        cout << setw(15) << "Lastname";
        cout << setw(15) << "ID";
        cout << setw(15) << "Grade" << endl;
        if (courseInfo.find(courseNum) == courseInfo.end()) {
            cout << "Course not found." << endl;
            return;
        } else {
            for (const auto& studentPair : grades) {
            int studentID = studentPair.first;
            const auto& courseGrades = studentPair.second;

            if (courseGrades.find(courseNum) != courseGrades.end()) {
                const auto& student = studentInfo.at(studentID);
                const string& grade = courseGrades.at(courseNum);
                const auto& course = courseInfo.at(courseNum);

                cout << setw(15) << student.firstName
                     << setw(15) << student.lastName
                     << setw(15) << studentID
                     << setw(15) << grade << endl;
            }
        }
    }
}
}

//5. List students
void listStudents() {
    cout << setw(15) << "Firstname" << setw(15) << "Lastname" << setw(15) << "ID" << setw(15) << "Phone" << endl;
    cout << endl;

    for (const auto& pair : studentInfo) {
        const auto& id = pair.first;
        const auto& student = pair.second;

        cout << setw(15) << student.firstName << setw(15) << student.lastName << setw(15)
             << id << setw(15) << student.phoneNumber << endl;
    }
}

//6. Display course listing
void displayCourseListing() {
    cout << setw(15) << "CourseNumber" << setw(20) << "CourseName" << endl;
    for (const auto& coursePair : courseInfo) {
        cout << setw(15) << coursePair.first   // CourseNumber
             << setw(20) << coursePair.second.courseName  // CourseName
             << endl;
    }
}


//7.Exit
void saveAndExit() {
    // Open files for writing
    ofstream studentFile("student.out");
    ofstream courseFile("course.out");
    ofstream gradeFile("grade.out");

    if (!studentFile || !courseFile || !gradeFile) {
        cerr << "Error: Unable to open output files for saving." << endl;
        return;
    }

    studentFile << "Firstname" << setw(15) << "Lastname" << setw(15) << "ID" << setw(15) << "Phone" << endl;
    courseFile << "CourseNumber" << setw(15) << "CourseName" << endl;
    gradeFile << "StudentID" << setw(15) << "CourseNumber" << setw(15) << "Grade" << endl;

    for (const auto& pair : studentInfo) {
        int id = pair.first;
        const Student& student = pair.second;
        studentFile << student.firstName << setw(15) << student.lastName << setw(15)
                    << id << setw(15) << student.phoneNumber << endl;
    }

    for (const auto& pair : courseInfo) {
        const string& courseNumber = pair.first;
        const Course& course = pair.second;
        courseFile << courseNumber << setw(15) << course.courseName << endl;
    }

    for (const auto& studentPair : grades) {
        int studentId = studentPair.first;
        const auto& courseGrades = studentPair.second;
        for (const auto& gradePair : courseGrades) {
            const string& courseNumber = gradePair.first;
            const string& grade = gradePair.second;
            gradeFile << studentId << setw(15) << courseNumber << setw(15) << grade << endl;
        }
    }

    studentFile.close();
    courseFile.close();
    gradeFile.close();

    cout << "Data saved successfully to student.out, course.out, and grade.out.\n";
    cout << "Exiting the program. Goodbye!\n";
}
