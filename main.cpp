// main.cpp
// Console menu for the Smart Task Scheduler.
// Pending tasks live in the TaskHeap. Completed tasks live in a separate vector,
// so they never appear as pending.

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include "src/Task.h"
#include "src/TaskHeap.h"

using namespace std;

TaskHeap pendingTasks;
vector<Task> completedTasks;

// ---------------- Input helpers (validation) ----------------

// Reads one line. If the input ends (Ctrl+D / end of file), the program exits safely.
string readLine(const string& message) {
    cout << message;
    string line;
    if (!getline(cin, line)) {
        cout << "\nInput ended. Exiting." << endl;
        exit(0);
    }
    // remove spaces at the start and end
    size_t start = line.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }
    size_t end = line.find_last_not_of(" \t\r\n");
    return line.substr(start, end - start + 1);
}

bool isAllDigits(const string& text) {
    if (text.empty()) {
        return false;
    }
    for (size_t i = 0; i < text.size(); i++) {
        if (!isdigit((unsigned char)text[i])) {
            return false;
        }
    }
    return true;
}

int readInt(const string& message) {
    while (true) {
        string line = readLine(message);
        if (isAllDigits(line) && line.size() <= 6) {
            return atoi(line.c_str());
        }
        cout << "Please enter a valid number." << endl;
    }
}

string readNonEmptyText(const string& message) {
    while (true) {
        string line = readLine(message);
        if (!line.empty()) {
            return line;
        }
        cout << "Input cannot be empty." << endl;
    }
}

int readPriority() {
    while (true) {
        int choice = readInt("Select priority (1 = High, 2 = Medium, 3 = Low): ");
        if (choice >= 1 && choice <= 3) {
            return choice;
        }
        cout << "Priority must be 1, 2 or 3." << endl;
    }
}

// Checks format yyyy-MM-dd and whether the day really exists
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }
    string yearPart = date.substr(0, 4);
    string monthPart = date.substr(5, 2);
    string dayPart = date.substr(8, 2);

    if (!isAllDigits(yearPart) || !isAllDigits(monthPart) || !isAllDigits(dayPart)) {
        return false;
    }

    int year = atoi(yearPart.c_str());
    int month = atoi(monthPart.c_str());
    int day = atoi(dayPart.c_str());

    if (year < 2000 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && leapYear) {
        maxDay = 29;
    }
    return day <= maxDay;
}

string readDeadline() {
    while (true) {
        string date = readNonEmptyText("Enter deadline (yyyy-MM-dd, e.g. 2025-03-15): ");
        if (isValidDate(date)) {
            return date;
        }
        cout << "Invalid date. Use the format yyyy-MM-dd with a real date." << endl;
    }
}

// ---------------- Menu ----------------

void printMenu() {
    cout << endl;
    cout << "===== SMART TASK SCHEDULER =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View All Tasks" << endl;
    cout << "3. View Next Important Task" << endl;
    cout << "4. Search Task" << endl;
    cout << "5. Mark Task as Completed" << endl;
    cout << "6. Exit" << endl;
}

// ---------------- Feature 1: Add Task ----------------
void addTask() {
    string name = readNonEmptyText("Enter task name: ");

    if (pendingTasks.findIndexByName(name) != -1) {
        cout << "A pending task with this name already exists. Use a different name." << endl;
        return;
    }

    int priority = readPriority();
    string deadline = readDeadline();

    Task newTask(name, priority, deadline);
    pendingTasks.insert(newTask);
    cout << "Task added successfully." << endl;
}

// ---------------- Feature 2: View All Tasks ----------------
void viewAllTasks() {
    if (pendingTasks.isEmpty()) {
        cout << "No pending tasks." << endl;
    } else {
        vector<Task> sorted = pendingTasks.getSortedTasks();
        cout << endl;
        cout << "--- Pending Tasks (most important first) ---" << endl;
        cout << "No  Name                 | Priority | Deadline   | Status" << endl;
        for (size_t i = 0; i < sorted.size(); i++) {
            cout << (i + 1) << ".  " << sorted[i].toString() << endl;
        }
    }

    if (!completedTasks.empty()) {
        cout << endl;
        cout << "--- Completed Tasks ---" << endl;
        for (size_t i = 0; i < completedTasks.size(); i++) {
            cout << (i + 1) << ".  " << completedTasks[i].toString() << endl;
        }
    }
}

// ---------------- Feature 3: Next Important Task ----------------
void viewNextTask() {
    if (pendingTasks.isEmpty()) {
        cout << "No pending tasks." << endl;
    } else {
        cout << endl;
        cout << "Next task to complete:" << endl;
        cout << pendingTasks.peek().toString() << endl;
    }
}

// ---------------- Feature 4: Search Task (Linear Search) ----------------
void searchTask() {
    string keyword = readNonEmptyText("Enter task name to search: ");
    bool found = false;

    vector<Task> pendingMatches = pendingTasks.searchByKeyword(keyword);
    for (size_t i = 0; i < pendingMatches.size(); i++) {
        cout << pendingMatches[i].toString() << endl;
        found = true;
    }

    // Linear search in the completed list
    string lowerKeyword = toLowerCase(keyword);
    for (size_t i = 0; i < completedTasks.size(); i++) {
        if (toLowerCase(completedTasks[i].getName()).find(lowerKeyword) != string::npos) {
            cout << completedTasks[i].toString() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No task found with that name." << endl;
    }
}

// ---------------- Feature 5: Complete Task ----------------
void completeTask() {
    if (pendingTasks.isEmpty()) {
        cout << "No pending tasks to complete." << endl;
        return;
    }

    string name = readNonEmptyText("Enter the exact name of the task to complete: ");
    Task done("", 3, "");

    if (!pendingTasks.removeByName(name, done)) {
        cout << "No pending task found with that name." << endl;
    } else {
        done.markCompleted();
        completedTasks.push_back(done);
        cout << "Task marked as completed: " << done.getName() << endl;
    }
}

// ---------------- Main ----------------
int main() {
    bool running = true;

    while (running) {
        printMenu();
        int choice = readInt("Enter your choice (1-6): ");

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewAllTasks();
                break;
            case 3:
                viewNextTask();
                break;
            case 4:
                searchTask();
                break;
            case 5:
                completeTask();
                break;
            case 6:
                running = false;
                cout << "Goodbye! Stay productive." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number from 1 to 6." << endl;
        }
    }
    return 0;
}
