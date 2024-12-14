#include <iostream>
#include <set>
#include <string>
using namespace std;
template <typename T>
class MSet {
private:
    multiset<T> elements;

public:
    void add(const T& element) {
        elements.insert(element);
    }

    void remove(const T& element) {
        auto it = elements.find(element);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }

    bool contains(const T& element) const {
        return elements.find(element) != elements.end();
    }

    void display() const {
        for (const auto& element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }
};

void displayMenu() {
    cout << "1. Add element\n";
    cout << "2. Remove element\n";
    cout << "3. Check if element exists\n";
    cout << "4. Display elements\n";
    cout << "5. Exit\n";
}

template <typename T>
void handleMSet() {
    MSet<T> mset;
    int choice;
    T element;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter element to add: ";
            cin >> element;
            mset.add(element);
            break;
        case 2:
            cout << "Enter element to remove: ";
            cin >> element;
            mset.remove(element);
            break;
        case 3:
            cout << "Enter element to check: ";
            cin >> element;
            if (mset.contains(element)) {
                cout << "Element exists in the set.\n";
            }
            else {
                cout << "Element does not exist in the set.\n";
            }
            break;
        case 4:
            mset.display();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

int main() {
    int typeChoice;
    cout << "Choose type of elements:\n";
    cout << "1. int\n";
    cout << "2. double\n";
    cout << "3. string\n";
    cout << "Enter your choice: ";
    cin >> typeChoice;

    switch (typeChoice) {
    case 1:
        handleMSet<int>();
        break;
    case 2:
        handleMSet<double>();
        break;
    case 3:
        handleMSet<string>();
        break;
    default:
        cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}
