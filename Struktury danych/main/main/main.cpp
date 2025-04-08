#include <iostream>
#include <chrono>
#include "DynamicArray.h"
#include "LinkedList.h"

using namespace std;
using namespace chrono;

// Funkcja do pomiaru czasu wykonania operacji
template <typename T>
void measureOperationTime(void(*operation)(T&), T& dataStructure, const string& operationName) {
    auto start = high_resolution_clock::now();
    operation(dataStructure);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken for " << operationName << ": " << duration.count() << " ms\n";
}

// Dodawanie na koniec
template <typename T>
void addToEnd(T& structure) {
    structure.addToEnd(10);
}

// Dodawanie na początek
template <typename T>
void addToStart(T& structure) {
    structure.addToStart(10);
}

// Dodawanie w wybranym indeksie
template <typename T>
void addAtIndex(T& structure) {
    structure.addAtIndex(3, 10);
}

// Usuwanie z początku
template <typename T>
void removeFromStart(T& structure) {
    structure.removeFromStart();
}

// Usuwanie z końca
template <typename T>
void removeFromEnd(T& structure) {
    structure.removeFromEnd();
}

// Usuwanie z wybranego indeksu
template <typename T>
void removeAtIndex(T& structure) {
    structure.removeAtIndex(2);
}

int main() {
    int operationChoice;
    cout << "Choose operation:\n";
    cout << "1. Add to End\n";
    cout << "2. Add to Start\n";
    cout << "3. Add at Index\n";
    cout << "4. Remove from Start\n";
    cout << "5. Remove from End\n";
    cout << "6. Remove at Index\n";
    cout << "Enter choice (1-6): ";
    cin >> operationChoice;

    // DynamicArray i LinkedList
    DynamicArray<int> dynamicArray;
    LinkedList<int> linkedList;

    // Perform the selected operation and measure time
    switch (operationChoice) {
    case 1:
        measureOperationTime(addToEnd, dynamicArray, "Adding to End (DynamicArray)");
        measureOperationTime(addToEnd, linkedList, "Adding to End (LinkedList)");
        break;
    case 2:
        measureOperationTime(addToStart, dynamicArray, "Adding to Start (DynamicArray)");
        measureOperationTime(addToStart, linkedList, "Adding to Start (LinkedList)");
        break;
    case 3:
        measureOperationTime(addAtIndex, dynamicArray, "Adding at Index (DynamicArray)");
        measureOperationTime(addAtIndex, linkedList, "Adding at Index (LinkedList)");
        break;
    case 4:
        measureOperationTime(removeFromStart, dynamicArray, "Removing from Start (DynamicArray)");
        measureOperationTime(removeFromStart, linkedList, "Removing from Start (LinkedList)");
        break;
    case 5:
        measureOperationTime(removeFromEnd, dynamicArray, "Removing from End (DynamicArray)");
        measureOperationTime(removeFromEnd, linkedList, "Removing from End (LinkedList)");
        break;
    case 6:
        measureOperationTime(removeAtIndex, dynamicArray, "Removing at Index (DynamicArray)");
        measureOperationTime(removeAtIndex, linkedList, "Removing at Index (LinkedList)");
        break;
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
