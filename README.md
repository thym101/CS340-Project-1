# CS340 Project 1
Thy Mai - StudentID: 800764674

## Project Summary
This project is a menu-driven program that helps manage the data of students, courses, and grades for a university. It first reads input from .dat files, displays a menu where users can perform several operations on the data, such as adding, removing, displaying, and updating information, and saves the updated data to .out files upon exit. This program provides a user-friendly interface to efficiently manage university data.

## Brief information for functions
### 1. read function:
Reads data from .dat files, stores the data into nested hash maps, and prints an error message if the file fails to open.

### 2. modifyGrade ():
Adds a new grade or modifies an existing grade. Prints an error message if the student ID or course does not exist or if the grade letter is invalid.

### 3. removeGrade():
Removes a grade for a specific student and course. Prints an error message if the student ID or course does not exist.

### 4. studentGradeReport():
Displays grade report(s) for a specific student or all students. Prints an error message if the student ID does not exist.

### 5. courseGradeReport():
Displays grade report(s) for a specific course or all courses. Prints an error message if the course number does not exist.

### 6. listStudents():
Displays a list of all students, including their first name, last name, ID, and phone number.

### 7. displayCourseListing():
Displays a list of all courses, including their course numbers and names.

### 8. saveAndExit():
Saves all data (after modifying) to .out files and exits the program.
 
## Data Structure: Nested Hash Map

### Brief Description of the Data Structure Used
For this project, I implemented:
#### 1. A hash map for students' data:
The key is the student ID, and the value is a Student struct containing the student's first name, last name, and phone number.
#### 2. A hash map for courses' data:
The key is the course number, and the value is a Course struct containing the course name.
#### 3. A nested hash map for grades:
+ The outer map uses the student ID as the key, and the value is an inner map which stores all the courses that specific student takes, along with the corresponding grades.
+ In the inner map, the course number is the key, and the grade is the value.

### Pros and cons
#### Pros:
+ No need to assign a specific size for the table, it grows dynamically as data is added or removed.
+ Accessing, updating, or deleting grades is very fast
+ Avoids duplicate storage of grades, unlike using two vectors of vectors.
+ Students, courses, and grades are stored in distinct maps, making the data more organized and easier to manage.
#### Cons:
+ The data is not stored in a specific order
+ Displaying grades of all for a specific course requires iterating through all students to check if they took the course.

### Reasons for choosing this structure
I choose this structure for 3 main reasons:
+ Students, courses, and grades are stored in distinct maps, making it easier to visualize, code, and manage data.
+ No need to worry about memory limitations
+ Time efficiency

### What I've learned from ChatGPT?
+ I had never used a nested hash map before, and ChatGPT helped me visualize how it works, making it easier to understand its structure and functionality. **I've learned a new data structure from this project!**
+ I learned the syntax and logic of nested hash map from both ChatGPT and searching on Goggle!
+ During the project, I encountered bugs, such as out-of-range exceptions when accessing maps, and I learned from ChatGPT why it happened and how to handle that error.
