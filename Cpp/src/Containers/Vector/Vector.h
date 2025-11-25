//
// Created by user on 24.11.25.
//

#ifndef VECTOR_H
#define VECTOR_H

constexpr int INITIAL_CAPACITY{10};

template<typename T>
class Vector {
public:
    ~Vector(); //done
    explicit Vector(int initial_capacity = INITIAL_CAPACITY); //done

    void push_back(int value); //done
    void pop_back(); //done
    void insert(int index, int value); //done
    void remove(int index); //done
    void clear(); //done
    [[nodiscard]] size_t get_size() const; //done
    [[nodiscard]] size_t get_capacity() const; //done
    [[nodiscard]] int at(T index) const; //done
    [[nodiscard]] T front() const; //done
    [[nodiscard]] T back() const; //done
    void print() const;

    //TODO ------------->
    //realize smart copy
    //realize [] operator
    //realize tests


private:
    T* data{};
    size_t capacity{0};
    size_t size{0};

    void expand();
    //void rellocate();//my feature::hard level

};

template<typename T>
int Vector<T>::at(T index) const {
    if (index > this->size || index < this->size)
        throw std::out_of_range("Vector::at() Index out of range");

    return this->data[index];
}

template<typename T>
size_t Vector<T>::get_size() const{
    return this->size;
}

template<typename T>
Vector<T>::Vector(int initial_capacity) {
    this->data = new int[initial_capacity];
    this->capacity = initial_capacity;
    this->size = 0;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] this->data;
}

template<typename T>
void Vector<T>::push_back(int value) {
    if(this->size == this->capacity)
        this->expand();
    this->data[this->size] = value;
    ++this->size;
}

template<typename T>
void Vector<T>::print() const {
    for(size_t i = 0; i < this->size; ++i)
        std::cout << this->data[i] << " ";
    std::cout << "\n";
}

template<typename T>
void Vector<T>::expand() {
    this->capacity *=2;
    int* newData = new int[this->capacity];
    for(size_t i = 0; i < this->size; ++i)
        newData[i] = this->data[i];
    delete[] this->data;
    this->data = newData;
}


template<typename T>
void Vector<T>::pop_back() {
    if (this->size == 0)
        throw std::out_of_range("Vector::pop_back() Index out of range");
   --this->size;
}

template<typename T>
void Vector<T>::clear() {
    this->data = new int[INITIAL_CAPACITY];
    this->capacity = INITIAL_CAPACITY;
    this->size = 0;
    delete[] this->data;
    this->data = nullptr;
}

template<typename T>
size_t Vector<T>::get_capacity() const {
    return this->capacity;
}

template<typename T>
void Vector<T>::insert(int index, int value) {
    if (index > this->size || index < 0) {
        throw std::out_of_range("Vector::insert() Index out of range");
    }


    if(this->size == this->capacity) {
        this->expand();
    }
    ++this->size;

   for(size_t i = this->size; i > index; --i)
       this->data[i] = this->data[i - 1];

    this->data[index] = value;
}

template<typename T>
void Vector<T>::remove(int index) {
    if (index > this->size || index < 0) {
        throw std::out_of_range("Vector::remove() Index out of range");
    }
    for (size_t i = index; i < this->size; ++i)
        this->data[i] = this->data[i + 1];
    --this->size;
}

template<typename T>
T Vector<T>::front() const {
    if (this->size == 0)
        throw std::out_of_range("Vector::front() vector is empty");
    return this->data[0];
}

template<typename T>
T Vector<T>::back() const {
    if (this->size == 0)
        throw std::out_of_range("Vector::back() vector is empty");
    return this->data[this->size - 1];
}

#endif //VECTOR_H
