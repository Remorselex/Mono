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

### 1. Базовые задачи (Манипуляции с индексами и In-Place изменение)
*В этих задачах тренируется механика сдвигов, перезаписи элементов "на месте" и работа с границами без выделения дополнительной памяти.*

- [27. Remove Element](https://leetcode.com/problems/remove-element/) (Easy) — *Классика на write_ptr*
- [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/) (Easy)
- [88. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/) (Easy) — *Слияние с конца массива*
- [80. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/) (Medium)
- [189. Rotate Array](https://leetcode.com/problems/rotate-array/) (Medium) — *Разворот массива по месту*
- [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/) (Easy) — *Сдвиг всех нулей в конец*
- [905. Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/) (Easy)
- [922. Sort Array By Parity II](https://leetcode.com/problems/sort-array-by-parity-ii/) (Easy)
- [1089. Duplicate Zeros](https://leetcode.com/problems/duplicate-zeros/) (Easy)

### 2. Двухуказательные задачи (Two Pointers)
*Встречные или догоняющие указатели для поиска пар, сумм или оптимизации перебора от O(n²) к O(n).*

- [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) (Medium)
- [15. 3Sum](https://leetcode.com/problems/3sum/) (Medium) — *Комбинация сортировки и двух указателей*
- [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/) (Medium)
- [18. 4Sum](https://leetcode.com/problems/4sum/) (Medium)
- [344. Reverse String](https://leetcode.com/problems/reverse-string/) (Easy) — *Простейший встречный обход*
- [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/) (Easy)
- [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/) (Medium)
- [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/) (Hard) — *Два указателя на пике эффективности*
- [611. Valid Triangle Number](https://leetcode.com/problems/valid-triangle-number/) (Medium)
- [844. Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/) (Easy)
- [977. Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/) (Easy)

### 3. Скользящее окно (Sliding Window)
*Паттерн динамического или фиксированного окна (левый и правый указатель) для поиска подмассивов, удовлетворяющих условиям.*

- [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) (Medium) — *Классическое расширение/сжатие окна*
- [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/) (Medium)
- [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) (Medium)
- [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) (Medium)
- [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/) (Medium)
- [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/) (Medium)
- [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/) (Hard) — *Сложная задача на контроль окна*
- [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/) (Medium)
- [1208. Get Equal Substrings Within Budget](https://leetcode.com/problems/get-equal-substrings-within-budget/) (Medium)

### 4. Сложные и комбинированные задачи (Префиксные суммы, Хэширование по индексам)
*Задачи, требующие нестандартного использования структуры: накопление сумм или использование значений как индексов (знаки +/-).*

- [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/) (Hard) — *Индексы массива как ячейки памяти*
- [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) (Easy)
- [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) (Medium) — *Алгоритм Флойда на массиве*
- [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) (Easy) — *База префиксных сумм*
- [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/) (Medium)
- [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/) (Medium)
- [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/) (Medium)
- [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/) (Medium)
- [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) (Medium) — *Алгоритм Кадана*

### 5. Двумерные массивы и Матрицы (2D Arrays)
*Работа со вложенными циклами, трансформацией координат и контролем границ сетки.*

- [48. Rotate Image](https://leetcode.com/problems/rotate-image/) (Medium) — *Поворот матрицы на 90 градусов in-place*
- [54. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) (Medium) — *Обход по спирали*
- [59. Spiral Matrix II](https://leetcode.com/problems/spiral-matrix-ii/) (Medium)
- [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/) (Medium)
- [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/) (Medium)
- [498. Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/) (Medium)
- [867. Transpose Matrix](https://leetcode.com/problems/transpose-matrix/) (Easy)
- [1260. Shift 2D Grid](https://leetcode.com/problems/shift-2d-grid/) (Easy)
- [1351. Count Negative Numbers in a Sorted Matrix](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/) (Easy)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Array Data Structure](https://www.geeksforgeeks.org/array-data-structure/)
- [cplusplus.com - Arrays](https://cplusplus.com/doc/tutorial/arrays/)