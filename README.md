# CS340 Project 1
Thy Mai - StudentID: 800764674

## Project Summary
This project is a menu-driven program that helps manage the data of students, courses, and grades for a university. It first reads input from .dat files, displays a menu where users can perform several operations on the data, such as adding, removing, displaying, and updating information, and saves the updated data to .out files upon exit. This program provides a user-friendly interface to efficiently manage university data.

## Brief information for functions
### read function:
Reads data from .dat files, stores the data into nested hash maps, and prints an error message if the file fails to open.

### 1. modifyGrade ():
Adds a new grade or modifies an existing grade. Prints an error message if the student ID or course does not exist or if the grade letter is invalid.

### 2. removeGrade():
Removes a grade for a specific student and course. Prints an error message if the student ID or course does not exist.

### 3. studentGradeReport():
Displays grade report(s) for a specific student or all students. Prints an error message if the student ID does not exist.

### 4. courseGradeReport():
Displays grade report(s) for a specific course or all courses. Prints an error message if the course number does not exist.

### 5. listStudents():
Displays a list of all students, including their first name, last name, ID, and phone number.

### 6. displayCourseListing():
Displays a list of all courses, including their course numbers and names.

### 7. saveAndExit():
Saves all data (after modifying) to .out files and exits the program.

