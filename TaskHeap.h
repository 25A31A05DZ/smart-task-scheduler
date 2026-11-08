// TaskHeap.h
// A hand-written Min Heap stored in an array (std::vector). It works as a Priority Queue.
// The "smallest" task (the most important one) is always at index 0 (the root).
//
// Array positions for a node at index i:
//   parent      = (i - 1) / 2
//   left child  = 2 * i + 1
//   right child = 2 * i + 2
//
// Only PENDING tasks are stored here.

#ifndef TASKHEAP_H
#define TASKHEAP_H

#include <vector>
#include <string>
#include <cctype>
#include "Task.h"

// Helper: converts text to lower case so searching ignores capital letters
inline std::string toLowerCase(const std::string& text) {
    std::string result = text;
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = (char)std::tolower((unsigned char)result[i]);
    }
    return result;
}

class TaskHeap {
private:
    std::vector<Task> heapArray;

    int getSize() const {
        return (int)heapArray.size();
    }

    void swapTasks(int i, int j) {
        Task temp = heapArray[i];
        heapArray[i] = heapArray[j];
        heapArray[j] = temp;
    }

    // Sift up: swap with the parent while this task is more important. O(log n)
    void siftUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heapArray[index].isMoreImportantThan(heapArray[parentIndex])) {
                swapTasks(index, parentIndex);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // HEAPIFY (sift down): push a task down until both children are less important. O(log n)
    void siftDown(int index) {
        int size = getSize();
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int best = index;

            if (left < size && heapArray[left].isMoreImportantThan(heapArray[best])) {
                best = left;
            }
            if (right < size && heapArray[right].isMoreImportantThan(heapArray[best])) {
                best = right;
            }
            if (best == index) {
                break;
            }
            swapTasks(index, best);
            index = best;
        }
    }

    // HEAP DELETION - O(log n)
    // Step 1: move the LAST task into this position.
    // Step 2: shrink the heap by one.
    // Step 3: fix the heap order using sift down (heapify) and sift up.
    Task removeAt(int index) {
        Task removed = heapArray[index];
        int lastIndex = getSize() - 1;

        if (index != lastIndex) {
            heapArray[index] = heapArray[lastIndex];
            heapArray.pop_back();
            siftDown(index);
            siftUp(index);
        } else {
            heapArray.pop_back();
        }
        return removed;
    }

public:
    bool isEmpty() const {
        return heapArray.empty();
    }

    // HEAP INSERTION - O(log n)
    // Step 1: put the new task at the end of the array.
    // Step 2: sift up - swap it with its parent while it is more important.
    void insert(const Task& task) {
        heapArray.push_back(task);
        siftUp(getSize() - 1);
    }

    // PEEK - O(1)
    // The most important task is always the root.
    // Call isEmpty() first: peeking an empty heap is not allowed.
    Task peek() const {
        return heapArray[0];
    }

    // LINEAR SEARCH (exact name) - O(n)
    // Check every task one by one. Returns the index, or -1 if not found.
    int findIndexByName(const std::string& name) const {
        for (int i = 0; i < getSize(); i++) {
            if (toLowerCase(heapArray[i].getName()) == toLowerCase(name)) {
                return i;
            }
        }
        return -1;
    }

    // LINEAR SEARCH (keyword) - O(n)
    // Returns all pending tasks whose name contains the keyword.
    std::vector<Task> searchByKeyword(const std::string& keyword) const {
        std::vector<Task> matches;
        std::string lowerKeyword = toLowerCase(keyword);
        for (int i = 0; i < getSize(); i++) {
            if (toLowerCase(heapArray[i].getName()).find(lowerKeyword) != std::string::npos) {
                matches.push_back(heapArray[i]);
            }
        }
        return matches;
    }

    // COMPLETE A TASK (by name) - O(n) search + O(log n) deletion
    // Returns true and fills removedTask if found, otherwise returns false.
    bool removeByName(const std::string& name, Task& removedTask) {
        int index = findIndexByName(name);
        if (index == -1) {
            return false;
        }
        removedTask = removeAt(index);
        return true;
    }

    // BASIC SORTING (Insertion Sort) - O(n^2)
    // Copies the heap into a new vector and sorts the COPY,
    // so the real heap is not disturbed.
    std::vector<Task> getSortedTasks() const {
        std::vector<Task> copy = heapArray;

        for (int i = 1; i < (int)copy.size(); i++) {
            Task current = copy[i];
            int j = i - 1;
            while (j >= 0 && current.isMoreImportantThan(copy[j])) {
                copy[j + 1] = copy[j];
                j--;
            }
            copy[j + 1] = current;
        }
        return copy;
    }
};

#endif
