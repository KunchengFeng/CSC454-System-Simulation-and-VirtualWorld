#pragma once
#include <Event.h>

class MinHeap {
private:
	Event* heap[100];
	int size;
	int maxSize;

	int parent(int position) { return (position - 1) / 2; }
	int leftChild(int position) { return (position * 2) + 1; }
	int rightChild(int position) { return (position * 2) + 2; }
	bool isLeaf(int position) { return (position > (size / 2)) && (position <= size); }
	

public:
	MinHeap() {
		size = 0;
		for (int i = 0; i < 100; i++) {
			heap[i] = NULL;
		}
		maxSize = 100;
	}

	void insert(Event* element) {
		if (size <= maxSize) {
			heap[size] = element;
			size++;

			int current = size - 1;
			int p = parent(current);
			while (heap[current] < heap[p] && current != p) {
				swap(heap[current], heap[p]);
				current = p;
				p = parent(current);
			}
		}
	};

	Event* get() {
		Event* min = heap[0];
		heap[0] = heap[size - 1];
		heap[size - 1] = NULL;
		size--;
		sort(0);
		return min;
	}

	bool remove(Event* element) {
		for (int i = 0; i < size; i++) {
			Event* temp = heap[i];
			if (temp == element) {
				heap[i] = heap[size - 1];
				heap[size - 1] = NULL;
				size--;
				sort(i);
				delete(temp);
				return true;
			}
		}
		return false;
	}

	Event* peak() { return heap[0]; }

	Event* seek(Event* element) {
		for (int i = 0; i < size; i++) {
			Event* temp = heap[i];
			if (element == temp) {
				return temp;
			}
		}
		return NULL;
	}

	void sort(int position) {
		if (!isLeaf(position)) {
			int leftChild = this->leftChild(position);
			int rightChild = this->rightChild(position);

			if (leftChild < size && rightChild < size) {
				if (heap[position] > heap[leftChild] || heap[position] > heap[rightChild]) {
					if (heap[leftChild] > heap[rightChild]) {
						swap(heap[position], heap[rightChild]);
						sort(rightChild);
					}
					else {
						swap(heap[position], heap[leftChild]);
						sort(leftChild);
					}
				}
			}
			else if (leftChild < size) {
				if (heap[position] > heap[leftChild]) {
					swap(heap[position], heap[leftChild]);
					sort(leftChild);
				}
			}
		}
	}

	bool hasNext() { return size != 0; }
};

