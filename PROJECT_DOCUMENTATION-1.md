# Smart Task Scheduler - Project Documentation

## 1. Project Introduction
Smart Task Scheduler is a console-based C++ application that arranges a student's daily tasks by priority
and deadline. It uses a Priority Queue built on a Min Heap, written by hand to show how the data structure works.

## 2. Problem Statement
Students handle many tasks (assignments, exams, records) with different importance and deadlines. Doing them
in the order they were written often causes urgent work to be missed. A system is needed that always shows
the most important task first.

## 3. Objectives
- Implement a Priority Queue using a Min Heap stored in an array.
- Order tasks by priority, then by earlier deadline.
- Demonstrate heap insertion, deletion and heapify.
- Demonstrate Linear Search and basic sorting.
- Keep the program simple, correct and beginner-friendly.

## 4. Software Requirements
- A C++ compiler such as g++ (C++11 or higher), or a C++ IDE/compiler app on Android
- Any text editor or IDE
- Git (optional, for GitHub)
- No internet needed to run the program

## 5. Data Structures Used
| Data Structure | Where | Purpose |
|---|---|---|
| Array (`std::vector<Task>`) | `TaskHeap` | Stores the heap; grows automatically when full |
| Min Heap / Priority Queue | `TaskHeap` (`TaskHeap.h`) | Keeps the most important pending task at the root |
| Vector (`std::vector<Task>`) | `main.cpp` | Stores completed tasks |
| Class and objects | `Task` (`Task.h`) | Holds name, priority, deadline, status |

Heap index rules: parent = (i-1)/2, left child = 2i+1, right child = 2i+2.

## 6. Algorithms Used
1. **Priority comparison** (`isMoreImportantThan`): smaller priority number wins (High=1, Medium=2, Low=3). If equal, the earlier deadline wins. Deadlines in `yyyy-MM-dd` format compare correctly as text. O(1).
2. **Heap insertion**: place the task at the end of the array, then sift up while it is more important than its parent. O(log n).
3. **Heap deletion**: replace the removed position with the last task, reduce the size, then sift down and sift up to restore order. O(log n).
4. **Heapify (sift down)**: swap a task with its more important child until the heap order is correct. O(log n).
5. **Peek**: return the root. O(1).
6. **Linear search**: check each task one by one by name. O(n).
7. **Insertion sort**: sort a copy of the heap array for display, leaving the heap unchanged. O(n²).

## 7. System Workflow
1. Program shows the menu and reads the user's choice (validated).
2. **Add**: read name, priority, deadline (validated) -> heap insertion.
3. **View all**: copy heap -> insertion sort -> print pending, then completed tasks.
4. **Next task**: peek at the heap root.
5. **Search**: linear search in pending and completed tasks.
6. **Complete**: linear search by name -> heap deletion -> mark completed -> store in completed list.
7. **Exit**: loop ends and the program closes.

## 8. Sample Input and Output
Input: add "Submit ADSAA record" (High, 2025-03-20), "Study Heaps" (Medium, 2025-03-18),
"Buy notebook" (Low, 2025-03-10), "Prepare Viva" (High, 2025-03-15).

Option 3 output:
```
Next task to complete:
Prepare Viva         | High     | 2025-03-15 | Pending
```
Option 2 output:
```
1.  Prepare Viva         | High     | 2025-03-15 | Pending
2.  Submit ADSAA record  | High     | 2025-03-20 | Pending
3.  Study Heaps          | Medium   | 2025-03-18 | Pending
4.  Buy notebook         | Low      | 2025-03-10 | Pending
```
After completing "Prepare Viva", option 3 shows "Submit ADSAA record", and "Prepare Viva" appears only under Completed Tasks.

## 9. Time Complexity Analysis
| Operation | Time |
|---|---|
| Heap insertion | O(log n) |
| Heap deletion / heapify | O(log n) |
| Peek (next task) | O(1) |
| Linear search | O(n) |
| Complete task (search + deletion) | O(n) |
| View all (insertion sort) | O(n²) |
| Array growth (rare, handled by vector) | O(n) |

Space complexity: O(n).

## 10. Advantages and Limitations
**Advantages**
- Most important task is found instantly (O(1)).
- Adding a task is fast (O(log n)).
- Simple, readable code that clearly shows the heap logic.
- Works offline.

**Limitations**
- Tasks are stored only in memory and are lost when the program closes.
- Task names must be unique among pending tasks.
- View all uses O(n²) insertion sort, which is slow for very large lists.
- Deadlines are not checked against today's date.

## 11. Future Enhancements
- Save and load tasks from a file.
- Edit or delete tasks.
- Warn about overdue tasks.
- Use a faster sort such as heap sort for the full list.

## 12. Conclusion
The project shows how a Min Heap can work as a Priority Queue for task scheduling. Insertion, deletion and
heapify keep the most important task at the top, while linear search and basic sorting support the remaining
features. It stays within the required ADSAA topics and can be completed and tested in one day.
