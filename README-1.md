# Smart Task Scheduler

A console-based C++ application that helps students organize daily tasks by **priority** and **deadline**.
Built for the ADSAA (Advanced Data Structures and Algorithm Analysis) course. The core concept is a
**Priority Queue implemented from scratch using a Min Heap** (no built-in `std::priority_queue`).

## Features
- Add a task (name, priority High/Medium/Low, deadline)
- View all pending tasks in priority order (same priority: earlier deadline first)
- View the next most important task
- Search a task by name (Linear Search)
- Mark a task as completed (it no longer appears as pending)
- Input validation for wrong menu choices, empty names, invalid priority and invalid dates
- Exit safely

## Technologies Used
- C++ (C++11 or higher), compiled with g++
- Concepts: Priority Queue, Min Heap, Array (`std::vector`), Linear Search, Insertion Sort, Classes and Objects

## Project Structure
```
SmartTaskScheduler/
├── main.cpp             # Menu and input validation
├── src/
│   ├── Task.h           # Task class and priority comparison
│   └── TaskHeap.h       # Hand-written Min Heap (Priority Queue)
├── docs/
│   └── PROJECT_DOCUMENTATION.md
├── .gitignore
└── README.md
```

## How to Compile and Run
```bash
cd SmartTaskScheduler
g++ -std=c++11 main.cpp -o scheduler
./scheduler            # on Windows: scheduler.exe
```
On Android, open the files in a C++ IDE/compiler app and run `main.cpp`.

## Sample Output
```
===== SMART TASK SCHEDULER =====
1. Add Task
2. View All Tasks
3. View Next Important Task
4. Search Task
5. Mark Task as Completed
6. Exit
Enter your choice (1-6): 2

--- Pending Tasks (most important first) ---
No  Name                 | Priority | Deadline   | Status
1.  Prepare Viva         | High     | 2025-03-15 | Pending
2.  Submit ADSAA record  | High     | 2025-03-20 | Pending
3.  Study Heaps          | Medium   | 2025-03-18 | Pending
4.  Buy notebook         | Low      | 2025-03-10 | Pending
```

## Time Complexity
| Operation | Complexity |
|---|---|
| Add task (heap insertion) | O(log n) |
| Next important task (peek) | O(1) |
| Complete task (search + heap deletion) | O(n) + O(log n) = O(n) |
| Search task (linear search) | O(n) |
| View all (insertion sort on a copy) | O(n²) |

See `docs/PROJECT_DOCUMENTATION.md` for full documentation.
