#include "queue.h"

void menu() {
    Queue<int> intQueue;

    intQueue.enqueue(5);
    intQueue.enqueue(-10);
    intQueue.enqueue(15);
    intQueue.enqueue(-20);
    intQueue.enqueue(25);

    auto posIter = intQueue.getPositiveIterator();
    std::cout << "Positive elements: ";
    while (posIter.hasNext()) {
        std::cout << posIter.next() << " ";
    }
    std::cout << std::endl;

    auto negIter = intQueue.getNegativeIterator();
    std::cout << "Negative elements: ";
    while (negIter.hasNext()) {
        std::cout << negIter.next() << " ";
    }
    std::cout << std::endl;
}

int main() {
    menu();
    return 0;
}
