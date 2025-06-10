#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Define the Course structure
struct Course {
    string number;
    string name;
    vector<string> prerequisites;
};

// Global data structure (map for fast lookup and sorting)
map<string, Course> courseMap;

// Function to load courses from file
void LoadCourses(const string& filename) {
    courseMap.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        // Get course number
        getline(ss, token, ',');
        course.number = token;

        // Get course name
        getline(ss, token, ',');
        course.name = token;

        // Get prerequisites (if any)
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        // Add course to the map
        courseMap[course.number] = course;
    }

    cout << "Courses successfully loaded!\n";
}

// Function to print the course list sorted by course number
void PrintCourseList() {
    if (courseMap.empty()) {
        cout << "Please load the data structure first.\n";
        return;
    }

    cout << "\nHere is a sample schedule:\n" << endl;
    for (const auto& pair : courseMap) {
        cout << pair.second.number << ", " << pair.second.name << endl;
    }
    cout << endl;
}

// Function to print course details
void PrintCourse(const string& courseNumber) {
    string upperCourse = courseNumber;
    transform(upperCourse.begin(), upperCourse.end(), upperCourse.begin(), ::toupper);

    if (courseMap.find(upperCourse) == courseMap.end()) {
        cout << "Course not found.\n";
        return;
    }

    const Course& course = courseMap[upperCourse];
    cout << course.number << ", " << course.name << endl;

    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i != course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    else {
        cout << "Prerequisites: None\n";
    }
}

// Main menu
void ShowMenu() {
    int choice = 0;
    string filename;

    do {
        cout << "\n1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit\n\n";
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter file name to load: ";
            cin >> filename;
            LoadCourses(filename);
            break;
        case 2:
            PrintCourseList();
            break;
        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            PrintCourse(courseNumber);
            break;
        }
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;
        default:
            cout << choice << " is not a valid option.\n";
        }

    } while (choice != 9);
}

// Entry point
int main() {
    cout << "Welcome to the course planner." << endl;
    ShowMenu();
    return 0;
}