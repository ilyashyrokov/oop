#include <iostream>
#include "ShPtrArr.h"
#include <string>

using namespace std;

void testIntArray() {
    ShPtrArr<int> arr(new int[5] {1, 2, 3, 4, 5});
    cout << "Массив целых чисел: ";
    for (size_t i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Счетчик ссылок: " << arr.use_count() << endl;
}

void testDoubleArray() {
    ShPtrArr<double> arr(new double[3] {1.1, 2.2, 3.3});
    cout << "Массив вещественных чисел: ";
    for (size_t i = 0; i < 3; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Счетчик ссылок: " << arr.use_count() << endl;
}

void testStringArray() {
    ShPtrArr<string> arr(new string[3]{ "Hello", "World", "!" });
    cout << "Массив строк: ";
    for (size_t i = 0; i < 3; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Счетчик ссылок: " << arr.use_count() << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Работа с массивом int\n";
        cout << "2. Работа с массивом double\n";
        cout << "3. Работа с массивом string\n";
        cout << "0. Выход\n";
        cout << "Введите выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            testIntArray();
            break;
        case 2:
            testDoubleArray();
            break;
        case 3:
            testStringArray();
            break;
        case 0:
            cout << "Выход...\n";
            break;
        default:
            cout << "Неверный выбор!\n";
        }

    } while (choice != 0);

    return 0;
}