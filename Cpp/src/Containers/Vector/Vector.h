//
// Created by user on 24.11.25.
//

#ifndef VECTOR_H
#define VECTOR_H

constexpr int INITIAL_CAPACITY{10};

class Vector {
public:
    ~Vector(); //done
    explicit Vector(int initial_capacity = INITIAL_CAPACITY); //done

    void push_back(int value); //done
    void pop_back(); //done
    void insert(int index, int value); //done
    void remove(int index); //done
    void clear(); //done
    [[nodiscard]] int get_size() const; //done
    [[nodiscard]] int get_capacity() const; //done
    [[nodiscard]] int at(int index) const; //done
    int front(); //done
    int back(); //done
    void print() const;

    //TODO ------------->
    //realize smart copy
    //realize [] operator
    //realize tests


private:
    int* data;
    int initial_capacity{10};
    int capacity{0};
    int size{0};

    void expand();
    //void rellocate();//my feature::hard level

};

inline int Vector::at(int index) const {
    if (index > this->size || index < this->size)
        throw std::out_of_range("Vector::at() Index out of range");

    return this->data[index];
}

inline int Vector::get_size() const{
    return this->size;
}


inline Vector::Vector(int initial_capacity) {
    this->data = new int[initial_capacity];
    this->capacity = initial_capacity;
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
    for(int i = 0; i < this->size; ++i)
        std::cout << this->data[i] << " ";
    std::cout << "\n";
}

inline void Vector::expand() {
    this->capacity *=2;
    int* newData = new int[this->capacity];
    for(int i = 0; i < this->size; ++i)
        newData[i] = this->data[i];
    delete[] this->data;
    this->data = newData;
}


inline void Vector::pop_back() {
    if (this->size == 0)
        throw std::out_of_range("Vector::pop_back() Index out of range");
   this->size--;
}

inline void Vector::clear() {
    this->data = new int[INITIAL_CAPACITY];
    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
    delete[] this->data;
    this->data = nullptr;
}

inline int Vector::get_capacity() const {
    return this->capacity;
}


inline void Vector::insert(int index, int value) {
    if (index > this->size || index < 0) {
        throw std::out_of_range("Vector::insert() Index out of range");
    }


    if(this->size == this->capacity) {
        this->expand();
    }
    this->size++;

   for(int i = this->size; i > index; --i)
       this->data[i] = this->data[i - 1];

    this->data[index] = value;
}

inline void Vector::remove(int index) {
    if (index > this->size || index < 0) {
        throw std::out_of_range("Vector::remove() Index out of range");
    }
    for (int i = index; i < this->size; ++i)
        this->data[i] = this->data[i + 1];
    this->size--;
}

inline int Vector::front() const {
    if (this->size == 0)
        throw std::out_of_range("Vector::front() vector is empty");
    return this->data[0];
}

inline int Vector::back() const {
    if (this->size == 0)
        throw std::out_of_range("Vector::back() vector is empty");
    return this->data[this->size - 1];
}

#endif //VECTOR_H
