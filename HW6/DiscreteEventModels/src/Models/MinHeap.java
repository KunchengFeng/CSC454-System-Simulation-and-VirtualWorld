package Models;

import java.util.ArrayList;

public class MinHeap<T extends Comparable<T>> {
    private final ArrayList<T> heap;
    private int size;
    private final int maxSize;

    public MinHeap(int maxSize) {
        this.maxSize = maxSize;
        size = 0;
        heap = new ArrayList<>(maxSize);
    }

    private int parent(int position) {return (position - 1) / 2;}
    private int leftChild(int position) {return (2 * position) + 1;}
    private int rightChild(int position) {return (2 * position) + 2;}
    private boolean isLeaf(int position) {return (position > (size / 2)) && (position <= size);}

    private void swap(int first, int second) {
        T temp = heap.get(first);
        heap.set(first, heap.get(second));
        heap.set(second, temp);
    }

    public void insert(T element) {
        if (size <= maxSize) {
            heap.add(element);
            size++;

            int current = size - 1;
            while (heap.get(current).compareTo(heap.get(parent(current))) <= 0
                    && heap.get(current) != heap.get(parent(current))) {
                swap(current, parent(current));
                current = parent(current);
            }
        }
    }

    public T remove() {
        T min = heap.get(0);
        heap.set(0, heap.get(size - 1));
        heap.remove(size - 1);
        size--;
        sort(0);
        return min;
    }

    public boolean remove(T element) {
        for (int i = 0; i < size; i++) {
            T temp = heap.get(i);
            if (temp == element) {
                heap.set(i, heap.get(size - 1));
                heap.remove(size - 1);
                size--;
                sort(i);
                return true;
            }
        }
        return false;
    }

    public T peak() {return heap.get(0);}

    public T seek(T element) {
        for (int i = 0; i < size; i++) {
            T temp = heap.get(i);
            if (element.compareTo(temp) == 0) {
                return temp;
            }
        }
        return null;
    }

    public boolean hasNext() {return heap.size() != 0;}

    // Sort to top to bottom and from smallest to biggest
    public void sort(int position) {
        if (!isLeaf(position)) {
            int leftChild = leftChild(position);
            int rightChild = rightChild(position);

            if (leftChild < size && rightChild < size) {    // Normal case
                if (heap.get(position).compareTo(heap.get(leftChild)) > 0 ||
                heap.get(position).compareTo(heap.get(rightChild)) > 0) {
                    int result = heap.get(leftChild).compareTo(heap.get(rightChild));
                    if (result < 0) {
                        swap(position, leftChild);
                        sort(leftChild);
                    } else {
                        swap(position, rightChild);
                        sort(rightChild);
                    }
                }
            } else if (leftChild < size) {                  // Only have a left child
                if (heap.get(position).compareTo(heap.get(leftChild)) > 0) {
                    swap(position, leftChild);
                    sort(leftChild);
                }
            }
        }
    }
}
