package Models;

public class Queue<Element> {
    private Node<Element> head;

    public Queue() {head = null;}

    public void enqueue(Element element) {
        if (head != null) {
            head.enqueue(element);
        } else {
            head = new Node<>(element);
        }
    }

    public Element dequeue() {
        if (head != null) {
            Node<Element> temp = head;
            head = head.next;
            return temp.element;
        } else {
            return null;
        }
    }

    public Element peak() {
        if (head != null) {
            return head.element;
        } else {
            return null;
        }
    }

    public Element peak(int position) {
        if (head != null) {
            return head.peak(0, position);
        } else {
            return null;
        }
    }

    public boolean hasNext() {
        return head != null;
    }

    public int count() {
        if (head != null) {
            return head.count();
        } else {
            return 0;
        }
    }
}

class Node<Element> {
    Node<Element> next;
    Element element;

    Node(Element element) {this.element = element;}

    void enqueue(Element element) {
        if (next != null) {
            next.enqueue(element);
        } else {
            next = new Node<>(element);
        }
    }

    int count() {
        if (next != null) {
            return next.count() + 1;
        } else {
            return 1;
        }
    }

    Element peak(int current, int target) {
        if (current == target) {
            return element;
        } else {
            if (next != null) {
                return next.peak(current + 1, target);
            } else {
                return null;
            }
        }
    }
}
