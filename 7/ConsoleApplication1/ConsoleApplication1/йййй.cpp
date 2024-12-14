#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
using namespace std;

class QueueException : public  exception {
private:
     string message;
public:
    explicit QueueException(const  string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class IteratorInterface {
public:
    virtual bool hasNext() const = 0;
    virtual int next() = 0;
    virtual ~IteratorInterface() = default;
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
         swap(ptr, other.ptr);
         swap(ref_count, other.ref_count);
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
     list<ShPtrArr<T>> container;

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
        return *(container.front().get());
    }

    size_t size() const {
        return container.size();
    }

    bool empty() const {
        return container.empty();
    }

    class PositiveIterator : public IteratorInterface {
    private:
        typename  list<ShPtrArr<T>>::iterator current;
        typename  list<ShPtrArr<T>>::iterator end;

        void advanceToNextPositive() {
            while (current != end && *(current->get()) <= 0) {
                ++current;
            }
        }

    public:
        PositiveIterator(typename  list<ShPtrArr<T>>::iterator start, typename  list<ShPtrArr<T>>::iterator end)
            : current(start), end(end) {
            advanceToNextPositive();
        }

        bool hasNext() const override {
            return current != end;
        }

        int next() override {
            if (!hasNext()) {
                throw QueueException("No more positive elements.");
            }
            int value = *(current->get());
            ++current;
            advanceToNextPositive();
            return value;
        }
    };

    class NegativeIterator : public IteratorInterface {
    private:
        typename  list<ShPtrArr<T>>::iterator current;
        typename  list<ShPtrArr<T>>::iterator end;

        void advanceToNextNegative() {
            while (current != end && *(current->get()) >= 0) {
                ++current;
            }
        }

    public:
        NegativeIterator(typename  list<ShPtrArr<T>>::iterator start, typename  list<ShPtrArr<T>>::iterator end)
            : current(start), end(end) {
            advanceToNextNegative();
        }

        bool hasNext() const override {
            return current != end;
        }

        int next() override {
            if (!hasNext()) {
                throw QueueException("No more negative elements.");
            }
            int value = *(current->get());
            ++current;
            advanceToNextNegative();
            return value;
        }
    };

    PositiveIterator getPositiveIterator() {
        return PositiveIterator(container.begin(), container.end());
    }

    NegativeIterator getNegativeIterator() {
        return NegativeIterator(container.begin(), container.end());
    }
};

void menu() {
    Queue<int> intQueue;

    intQueue.enqueue(5);
    intQueue.enqueue(-10);
    intQueue.enqueue(15);
    intQueue.enqueue(-20);
    intQueue.enqueue(25);

    auto posIter = intQueue.getPositiveIterator();
    cout << "Positive elements: ";
    while (posIter.hasNext()) {
        cout << posIter.next() << " ";
    }
    cout << endl;

    auto negIter = intQueue.getNegativeIterator();
    cout << "Negative elements: ";
    while (negIter.hasNext()) {
        cout << negIter.next() << " ";
    }
    cout << endl;
}

int main() {
    menu();
    return 0;
}
