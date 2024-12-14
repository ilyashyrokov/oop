#include <iostream>

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
#pragma once
