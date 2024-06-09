#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

struct Course {
    std::string name;
    int credits;
    double grade;
};

double convertToGradePoint(double grade, char gradingSystem) {
    switch(gradingSystem) {
        case 'A':
            if (grade >= 90) return 9.9;
            else if (grade >= 80) return 8.0;
            else if (grade >= 70) return 7.0;
            else if (grade >= 60) return 6.0;
            else if (grade >= 50) return 5.0;
            else if (grade >= 40) return 4.0;
            else if (grade >= 30) return 3.0;
            else if (grade >= 20) return 2.0;
            else if (grade >= 10) return 1.0;
            else return 0.0;
        // Add more grading systems if necessary
        default:
            return 0.0;
    }
}

double calculateCGPA(const std::vector<Course>& courses, char gradingSystem) {
    double totalPoints = 0.0;
    int totalCredits = 0;

    for (const auto& course : courses) {
        double gradePoint = convertToGradePoint(course.grade, gradingSystem);
        totalPoints += gradePoint * course.credits;
        totalCredits += course.credits;
    }

    return (totalCredits > 0) ? (totalPoints / totalCredits) : 0.0;
}

void displayMenu() {
    std::cout << "CGPA Calculator\n";
    std::cout << "Click A to start: ";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    std::string studentName;
    std::string grNumber;
    std::vector<Course> courses;
    int numCourses;
    char gradingSystem;

    std::cout << "Enter student name: ";
    std::getline(std::cin, studentName);
    std::cout << "Enter GR number: ";
    std::getline(std::cin, grNumber);

    displayMenu();
    std::cin >> gradingSystem;

    while (gradingSystem != 'A') {
        std::cerr << "Invalid grading system. Please enter A: ";
        std::cin >> gradingSystem;
    }
    
    std::cout << "Enter the number of courses: ";
    std::cin >> numCourses;

    while (numCourses <= 0) {
        std::cerr << "Invalid number of courses. Please enter a positive number: ";
        std::cin >> numCourses;
    }

    clearInputBuffer();

    for (int i = 0; i < numCourses; ++i) {
        Course course;
        std::cout << "Enter course name: ";
        std::getline(std::cin, course.name);
        std::cout << "Enter course credits: ";
        std::cin >> course.credits;
        std::cout << "Enter course grade: ";
        std::cin >> course.grade;

        // Input validation
        while (course.credits <= 0 || course.grade < 0 || course.grade > 100) {
            std::cerr << "Invalid input. Please enter valid credits and grades.\n";
            std::cout << "Re-enter course credits: ";
            std::cin >> course.credits;
            std::cout << "Re-enter course grade: ";
            std::cin >> course.grade;
        }

        courses.push_back(course);
        clearInputBuffer();
    }

    double cgpa = calculateCGPA(courses, gradingSystem);
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nStudent Name: " << studentName << "\n";
    std::cout << "GR Number: " << grNumber << "\n";
    std::cout << "Your CGPA is: " << cgpa << "\n";

    std::cout << "Course Breakdown:\n";
    for (const auto& course : courses) {
        std::cout << course.name << " (Credits: " << course.credits 
                  << ", Grade: " << course.grade << ")\n";
    }

    return 0;
}
