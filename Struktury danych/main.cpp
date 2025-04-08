#include <iostream>
#include <chrono>


using namespace std;
using namespace std::chrono;


// --------------------------------------------------
// Implementacja tablicy dynamicznej
template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int length;

    void resize() {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < length; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

public:
    DynamicArray(int initialCapacity)
        : capacity(initialCapacity), length(0) {
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void addToEnd(T value) {
        if (length == capacity)
            resize();
        data[length++] = value;
    }

    void addToStart(T value) {
        if (length == capacity)
            resize();
        for (int i = length; i > 0; i--)
            data[i] = data[i - 1];
        data[0] = value;
        length++;
    }

    void addAtIndex(int index, T value) {
        if (index < 0 || index > length) return;
        if (length == capacity)
            resize();
        for (int i = length; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        length++;
    }

    void removeFromStart() {
        if (length == 0) return;
        for (int i = 0; i < length - 1; i++)
            data[i] = data[i + 1];
        length--;
    }

    void removeFromEnd() {
        if (length > 0) length--;
    }

    void removeAtIndex(int index) {
        if (index < 0 || index >= length) return;
        for (int i = index; i < length - 1; i++)
            data[i] = data[i + 1];
        length--;
    }

    int search(T value) {
        for (int i = 0; i < length; i++)
            if (data[i] == value) return i;
        return -1;
    }
};

// --------------------------------------------------
// Implementacja listy wiązanej
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int length;

public:
    LinkedList() : head(nullptr), length(0) {}

    void addToEnd(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        length++;
    }

    void addToStart(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        length++;
    }

    void addAtIndex(int index, T value) {
        if (index < 0 || index > length) return;
        Node<T>* newNode = new Node<T>(value);
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<T>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
        length++;
    }

    void removeFromStart() {
        if (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            length--;
        }
    }

    void removeFromEnd() {
        if (head) {
            if (!head->next) {
                delete head;
                head = nullptr;
            } else {
                Node<T>* temp = head;
                while (temp->next && temp->next->next) {
                    temp = temp->next;
                }
                delete temp->next;
                temp->next = nullptr;
            }
            length--;
        }
    }

    void removeAtIndex(int index) {
        if (index < 0 || index >= length) return;
        if (index == 0) {
            removeFromStart();
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        Node<T>* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        length--;
    }

    int search(T value) {
        Node<T>* temp = head;
        int index = 0;
        while (temp) {
            if (temp->data == value) return index;
            temp = temp->next;
            index++;
        }
        return -1;
    }
};

void testDynamicArray(int repetitions) {
    DynamicArray<int> arr(5);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        arr.addToEnd(i);
    }
    auto stop = high_resolution_clock::now();
    cout << "DynamicArray - Average time addToEnd: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    DynamicArray<int> arr2(5);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        arr2.addToStart(i);
    }
    stop = high_resolution_clock::now();
    cout << "DynamicArray - Average time addToStart: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    DynamicArray<int> arr3(5);
    for (int i = 0; i < repetitions; i++) arr3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        arr3.addAtIndex(3, i);
    }
    stop = high_resolution_clock::now();
    cout << "DynamicArray - Average time addAtIndex: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    for (int i = 0; i < repetitions; i++) arr3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        arr3.removeFromStart();
    }
    stop = high_resolution_clock::now();
    cout << "DynamicArray - Average time removeFromStart: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    for (int i = 0; i < repetitions; i++) arr3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        arr3.removeFromEnd();
    }
    stop = high_resolution_clock::now();
    cout << "DynamicArray - Average time removeFromEnd: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    for (int i = 0; i < repetitions; i++) arr3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        arr3.removeAtIndex(1);
    }
    stop = high_resolution_clock::now();
    cout << "DynamicArray - Average time removeAtIndex: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    arr3.addToEnd(777);
    start = high_resolution_clock::now();
    int index = arr3.search(777);
    stop = high_resolution_clock::now();
    cout << "DynamicArray - Search time: " << duration_cast<nanoseconds>(stop - start).count() << " ns\n";
    cout << "DynamicArray - Found index: " << index << "\n\n";
}

void testLinkedList(int repetitions) {
    LinkedList<int> list;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        list.addToEnd(i);
    }
    auto stop = high_resolution_clock::now();
    cout << "LinkedList - Average time addToEnd: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    LinkedList<int> list2;
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        list2.addToStart(i);
    }
    stop = high_resolution_clock::now();
    cout << "LinkedList - Average time addToStart: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    LinkedList<int> list3;
    for (int i = 0; i < repetitions; i++) list3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        list3.addAtIndex(3, i);
    }
    stop = high_resolution_clock::now();
    cout << "LinkedList - Average time addAtIndex: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    for (int i = 0; i < repetitions; i++) list3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        list3.removeFromStart();
    }
    stop = high_resolution_clock::now();
    cout << "LinkedList - Average time removeFromStart: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    for (int i = 0; i < repetitions; i++) list3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        list3.removeFromEnd();
    }
    stop = high_resolution_clock::now();
    cout << "LinkedList - Average time removeFromEnd: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    for (int i = 0; i < repetitions; i++) list3.addToEnd(i);
    start = high_resolution_clock::now();
    for (int i = 0; i < repetitions; i++) {
        list3.removeAtIndex(1);
    }
    stop = high_resolution_clock::now();
    cout << "LinkedList - Average time removeAtIndex: " << duration_cast<nanoseconds>(stop - start).count() / repetitions << " ns\n";

    list3.addToEnd(777);
    start = high_resolution_clock::now();
    int index = list3.search(777);
    stop = high_resolution_clock::now();
    cout << "LinkedList - Search time: " << duration_cast<nanoseconds>(stop - start).count() << " ns\n";
    cout << "LinkedList - Found index: " << index << "\n\n";
}


int main() {
    const int repetitions = 100000;

    testDynamicArray(repetitions);
    testLinkedList(repetitions);

    return 0;
}
