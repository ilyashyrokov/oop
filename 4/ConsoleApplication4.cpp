#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
using namespace std;

class QueueException : public std::exception {
private:
    std::string message;
public:
    explicit QueueException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

template<typename T>
class ShPtrArr {
private:
    T* ptr;
    size_t* ref_count;

    void increase_ref_count() {
        if (ref_count) {
            ++(*ref_count);
        }
    }

    void decrease_ref_count() {
        if (ref_count && --(*ref_count) == 0) {
            delete[] ptr;
            delete ref_count;
            ptr = nullptr;
            ref_count = nullptr;
        }
    }

public:
    ShPtrArr() : ptr(nullptr), ref_count(nullptr) {}

    ShPtrArr(T* p) : ptr(p), ref_count(new size_t(1)) {}

    ShPtrArr(const ShPtrArr<T>& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        increase_ref_count();
    }

    ShPtrArr& operator=(const ShPtrArr<T>& other) {
        if (this != &other) {
            decrease_ref_count();
            ptr = other.ptr;
            ref_count = other.ref_count;
            increase_ref_count();
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    void reset() {
        decrease_ref_count();
        ptr = nullptr;
        ref_count = nullptr;
    }

    void swap(ShPtrArr<T>& other) {
        std::swap(ptr, other.ptr);
        std::swap(ref_count, other.ref_count);
    }

    T& operator[](size_t index) {
        return ptr[index];
    }

    ~ShPtrArr() {
        decrease_ref_count();
    }

    size_t use_count() const {
        return (ref_count) ? *ref_count : 0;
    }
};

template<typename T>
class Queue {
private:
    std::list<ShPtrArr<T>> container; 
public:
    void enqueue(const T& value) {
        container.push_back(ShPtrArr<T>(new T(value)));
    }

    void dequeue() {
        if (container.empty()) {
            throw QueueException("Queue is empty! Cannot dequeue.");
        }
        container.pop_front();
    }

    T front() const {
        if (container.empty()) {
            throw QueueException("Queue is empty! Cannot access front.");
        }
        return *container.front().get();
    }

    size_t size() const {
        return container.size();
    }

    bool empty() const {
        return container.empty();
    }
};

void menu() {
    Queue<int> intQueue;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент (int)\n";
        cout << "2. Удалить элемент (int)\n";
        cout << "3. Показать первый элемент (int)\n";
        cout << "4. Проверить размер очереди (int)\n";
        cout << "5. Выйти\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1: {
                int value;
                cout << "Введите число: ";
                cin >> value;
                intQueue.enqueue(value);
                std::cout << "Элемент добавлен.\n";
                break;
            }
            case 2:
                intQueue.dequeue();
                cout << "Элемент удалён.\n";
                break;
            case 3:
                cout << "Первый элемент: " << intQueue.front() << "\n";
                break;
            case 4:
                cout << "Размер очереди: " << intQueue.size() << "\n";
                break;
            case 5:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор.\n";
            }
        }
        catch (const QueueException& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    } while (choice != 5);
}

int main() {
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}
