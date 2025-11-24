//
// Created by user on 24.11.25.
//

#ifndef VECTOR_H
#define VECTOR_H
#include <strings.h>

class Vector {
public:
    ~Vector();
    explicit Vector(size_t initial_capasity = 10);

    void push_back(int value);
    void pop_back();
    void insert(int index, int value);
    void remove(int index);
    void clear();
    [[nodiscard]] size_t get_size() const;
    int get_capacity();
    [[nodiscard]] int at(int index) const;
    int front();
    int back();
    void print() const;
    //void copy(); //my feature::hard level

private:
    int* data;
    size_t capacity{};
    size_t size{};

    void expand();
    //void rellocate();//my feature::hard level

};

inline int Vector::at(int index) const {
    if (index > this->size || index < this->size)
        throw std::out_of_range("Vector::at() Index out of range");

    return this->data[index];
}

inline size_t Vector::get_size() const{
    return this->size;
}


inline Vector::Vector(size_t initial_capasity) {
    this->data = new int[initial_capasity];
    this->capacity = initial_capasity;
    this->size = 0;
}

inline Vector::~Vector() {
    delete[] this->data;
}

inline void Vector::push_back(int value) {
    if(this->size == this->capacity)
        this->expand();
    this->data[this->size] = value;
    this->size++;
}

inline void Vector::print() const {
    for(size_t i = 0; i < this->size; ++i)
        std::cout << this->data[i] << " ";
    std::cout << "\n";
}

inline void Vector::expand() {
    this->capacity *=2;
    int* newData = new int[this->capacity];
    for(size_t i = 0; i < this->size; ++i)
        newData[i] = this->data[i];
    delete[] this->data;
    this->data = newData;
}


inline void Vector::pop_back() {
    if (this->size < 0)
        throw std::out_of_range("Vector::pop_back() Index out of range");
   this->size--;
}



#endif //VECTOR_H
