// Task.h
// Represents one task in the Smart Task Scheduler.
// Priority numbers: 1 = High, 2 = Medium, 3 = Low (smaller number = more important).
// Deadline format: yyyy-MM-dd (example: 2025-03-15).

#ifndef TASK_H
#define TASK_H

#include <string>
#include <sstream>
#include <iomanip>

class Task {
private:
    std::string name;
    int priority;
    std::string deadline;
    bool completed;

public:
    Task(std::string taskName, int taskPriority, std::string taskDeadline) {
        name = taskName;
        priority = taskPriority;
        deadline = taskDeadline;
        completed = false;
    }

    std::string getName() const {
        return name;
    }

    int getPriority() const {
        return priority;
    }

    std::string getDeadline() const {
        return deadline;
    }

    bool isCompleted() const {
        return completed;
    }

    void markCompleted() {
        completed = true;
    }

    std::string getPriorityText() const {
        if (priority == 1) {
            return "High";
        } else if (priority == 2) {
            return "Medium";
        } else {
            return "Low";
        }
    }

    std::string getStatusText() const {
        if (completed) {
            return "Completed";
        }
        return "Pending";
    }

    // Priority comparison (used by the heap and the sort).
    // Returns true if this task is MORE important than the other task.
    // Rule 1: smaller priority number wins (High before Medium before Low).
    // Rule 2: if priorities are equal, the earlier deadline wins.
    // Dates in yyyy-MM-dd format compare correctly as plain text.
    // Time complexity: O(1)
    bool isMoreImportantThan(const Task& other) const {
        if (priority != other.priority) {
            return priority < other.priority;
        }
        return deadline < other.deadline;
    }

    // Text used when printing a task
    std::string toString() const {
        std::ostringstream out;
        out << std::left << std::setw(20) << name << " | "
            << std::setw(8) << getPriorityText() << " | "
            << deadline << " | "
            << getStatusText();
        return out.str();
    }
};

#endif
