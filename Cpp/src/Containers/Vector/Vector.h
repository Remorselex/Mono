//
// Created by user on 24.11.25.
//

//TODO IMPORTANT------------->
// realize tests
// realize smart copy
//TODO IMPORTANT------------->

//TODO METHODS ------------->
// reserve()
// shrink_to_fit()
// emplace_back()
// emplace()
// swap()
//TODO METHODS ------------->

#ifndef VECTOR_H
#define VECTOR_H

constexpr size_t INITIAL_CAPACITY{10};

template<typename T>
class Vector {
public:
    ~Vector();

    explicit Vector(size_t initial_capacity = INITIAL_CAPACITY);

    const T &operator[](size_t index) const;

    T &operator[](size_t index);

    //move semantics
    Vector(Vector &&rValue) noexcept;

    Vector &operator=(Vector &&rValue) noexcept;

    //copy semantics
    Vector(const Vector &other);

    Vector &operator=(const Vector &other);

    //range based arrays support
    T *begin() { return this->data; }

    T *end() { return this->data + this->size; }


    const T *begin() const { return this->data; }

    const T *end() const { return this->data + this->size; }

    void push_back(T value);

    void push_back(T &&value);

    void pop_back();

    void insert(size_t index, T value);

    void remove(size_t index);

    void clear();

    void reset();

    bool empty();

    [[nodiscard]] size_t get_size() const;

    [[nodiscard]] size_t get_capacity() const;

    T &at(size_t index) const;

    [[nodiscard]] T &front() const;

    [[nodiscard]] T &back() const;

    void print() const;

private:
    T *data{};
    size_t capacity{0};
    size_t size{0};

    void expand();
};

template<typename T>
Vector<T>::Vector(const Vector &other)
        : capacity(other.capacity),
          size(other.size) {

    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }

};

template<typename T>
Vector<T> &Vector<T>::operator=(const Vector &other) {
    if (this != &other) {
        delete[] data;

        capacity = other.capacity;
        size = other.size;
        data = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(Vector &&rValue) noexcept
        : data(rValue.data),
          capacity(rValue.capacity),
          size(rValue.size) {

    rValue.data = nullptr;
    rValue.capacity = 0;
    rValue.size = 0;
}

template<typename T>
Vector<T> &Vector<T>::operator=(Vector &&rValue) noexcept {
    if (this != &rValue) {
        delete[] data;

        data = rValue.data;
        capacity = rValue.capacity;
        size = rValue.size;

        rValue.data = nullptr;
        rValue.capacity = 0;
        rValue.size = 0;
    }
    return *this;
}

template<typename T>
Vector<T>::Vector(size_t initial_capacity) {
    if (initial_capacity <= 0)
        throw std::out_of_range("Vector::Vector() initial_capacity must be more then zero");

    this->data = new T[initial_capacity];
    this->capacity = initial_capacity;
    this->size = 0;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] this->data;
}

template<typename T>
const T &Vector<T>::operator[](size_t index) const {
    if (index > this->size) {
        throw std::out_of_range("Vector::operator[]() Index out of range");
    }

    return this->data[index];
}

template<typename T>
T &Vector<T>::operator[](size_t index) {
    if (index > this->size) {
        throw std::out_of_range("Vector::operator[] Index out of range");
    }
    return this->data[index];
}


template<typename T>
T &Vector<T>::at(size_t index) const {
    if (index >= this->size)
        throw std::out_of_range("Vector::at() Index out of range");

    return this->data[index];
}

template<typename T>
size_t Vector<T>::get_size() const {
    return this->size;
}

template<typename T>
void Vector<T>::push_back(T value) {
    if (this->size == this->capacity)
        this->expand();
    this->data[this->size] = value;
    ++this->size;
}

template<typename T>
void Vector<T>::push_back(T &&value) {
    if (size == capacity)
        expand();
    data[size] = std::move(value);
    ++size;
}

template<typename T>
void Vector<T>::print() const {
    for (size_t i = 0; i < this->size; ++i)
        std::cout << this->data[i] << " ";
    std::cout << "\n";
}

template<typename T>
void Vector<T>::expand() {
    this->capacity *= 2;
    T *newData = new T[this->capacity];
    for (size_t i = 0; i < this->size; ++i)
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
    this->size = 0;
}

template<typename T>
void Vector<T>::reset() {
    delete[] this->data;
    this->data = new T[INITIAL_CAPACITY];
    capacity = INITIAL_CAPACITY;
    this->size = 0;
}


template<typename T>
size_t Vector<T>::get_capacity() const {
    return this->capacity;
}

template<typename T>
void Vector<T>::insert(size_t index, T value) {
    if (index > this->size) {
        throw std::out_of_range("Vector::insert() Index out of range");
    }

    if (this->size >= this->capacity) {
        this->expand();
    }

    ++this->size;

    for (size_t i = this->size; i > index; --i)
        this->data[i] = this->data[i - 1];

    this->data[index] = value;
}

template<typename T>
void Vector<T>::remove(size_t index) {
    if (index >= this->size) {
        throw std::out_of_range("Vector::remove() Index out of range");
    }
    for (size_t i = index; i < this->size; ++i) {
        if (i + 1 == this->size) {
            break;
        }
        this->data[i] = this->data[i + 1];
    }


    --this->size;
}

template<typename T>
T &Vector<T>::front() const {
    if (this->size == 0)
        throw std::out_of_range("Vector::front() vector is empty");
    return this->data[0];
}

template<typename T>
T &Vector<T>::back() const {
    if (this->size == 0)
        throw std::out_of_range("Vector::back() vector is empty");
    return this->data[this->size - 1];
}

template<typename T>
bool Vector<T>::empty() {
    return this->size == 0;
};

#endif //VECTOR_H
