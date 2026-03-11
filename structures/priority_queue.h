#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include "../models/region.h"

class PriorityQueue {
private:
    std::vector<Region> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[parent].urgency_score < heap[index].urgency_score) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();

        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left].urgency_score > heap[largest].urgency_score)
                largest = left;

            if (right < size && heap[right].urgency_score > heap[largest].urgency_score)
                largest = right;

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    void insert(Region r) {
        heap.push_back(r);
        heapifyUp(heap.size() - 1);
    }

    Region extractMax() {
        Region top = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return top;
    }

    bool empty() {
        return heap.empty();
    }
};

#endif