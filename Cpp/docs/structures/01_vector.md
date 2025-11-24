# Массив (Array)

## 📝 Описание
Массив - это базовая структура данных, которая хранит элементы одного типа в непрерывной области памяти.

## 🎯 Основные операции

### 1. Доступ к элементу по индексу
- **Сложность**: O(1)
- **Описание**: Получение значения элемента по его индексу

### 2. Поиск элемента
- **Сложность**: O(n)
- **Описание**: Поиск первого вхождения элемента в массиве

### 3. Вставка элемента
- **В конец**: O(1) амортизированное
- **В начало/середину**: O(n)
- **При переполнении**: O(n) (выделение новой памяти и копирование)

### 4. Удаление элемента
- **С конца**: O(1)
- **Из начала/середины**: O(n)

## 📋 Интерфейс
```cpp
class Array {
public:
    // Конструктор с начальной емкостью
    explicit Array(size_t initial_capacity = 10);
    
    // Деструктор
    ~Array();
    
    // Доступ к элементу по индексу
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    
    // Основные операции
    void push_back(int value);    // Добавление в конец
    void insert(size_t index, int value);  // Вставка по индексу
    void remove(size_t index);    // Удаление по индексу
    int find(int value) const;    // Поиск элемента
    
    // Вспомогательные методы
    size_t size() const;          // Текущий размер
    size_t capacity() const;      // Текущая вместимость
    bool empty() const;           // Проверка на пустоту
    
private:
    int* data_;          // Указатель на массив
    size_t size_;        // Текущий размер
    size_t capacity_;    // Вместимость
    
    void resize(size_t new_capacity);  // Изменение размера
};
```

## 🔍 Особенности реализации
1. **Динамическое расширение**: При заполнении массива его размер увеличивается в 1.5-2 раза
2. **Инвариант класса**: size_ ≤ capacity_
3. **Гарантии безопасности**: Проверка границ в отладочном режиме

## 📊 Сравнение с std::vector
| Операция | Наш Array | std::vector |
|----------|-----------|-------------|
| Доступ   | O(1)      | O(1)        |
| Вставка  | O(n)      | O(n)        |
| Удаление | O(n)      | O(n)        |
| Поиск    | O(n)      | O(n)        |
| Память   | 2*size_t + указатель | 3*size_t + указатель |

## 📌 Рекомендуемые задачи для реализации
1. **Базовые задачи**
   - [27. Remove Element](https://leetcode.com/problems/remove-element/)
   - [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)
   - [88. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

2. **Двухпоисковые задачи**
   - [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)
   - [15. 3Sum](https://leetcode.com/problems/3sum/)
   - [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/)

3. **Скользящее окно**
   - [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
   - [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/)
   - [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)

4. **Сложные задачи**
   - [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
   - [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
   - [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

5. **Дополнительные задачи**
   - [48. Rotate Image](https://leetcode.com/problems/rotate-image/)
   - [54. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)
   - [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Array Data Structure](https://www.geeksforgeeks.org/array-data-structure/)
- [cplusplus.com - Arrays](https://cplusplus.com/doc/tutorial/arrays/)
