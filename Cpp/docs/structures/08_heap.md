# Куча / Очередь с приоритетом (Heap/Priority Queue)

## 📝 Описание
Бинарная куча - это полное бинарное дерево, где каждый узел имеет значение больше (max-heap) или меньше (min-heap) своих дочерних узлов.

## 🎯 Основные операции
- `insert`: O(log n) - вставка элемента
- `extract_max`/`extract_min`: O(log n) - извлечение максимума/минимума
- `get_max`/`get_min`: O(1) - получение максимума/минимума
- `delete`: O(log n) - удаление произвольного элемента

## 📋 Интерфейс
```cpp
template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
    std::vector<T> heap;
    Compare comp;
    
    void heapify_up(size_t index);
    void heapify_down(size_t index);
    
public:
    void push(const T& value);
    void pop();
    const T& top() const;
    bool empty() const;
    size_t size() const;
    void update_priority(const T& old_value, const T& new_value);
};
```

## 📌 15 фундаментальных задач
1. **Базовые операции**
   - [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)
   - [1046. Last Stone Weight](https://leetcode.com/problems/last-stone-weight/)
   - [2558. Take Gifts From the Richest Pile](https://leetcode.com/problems/take-gifts-from-the-richest-pile/)

2. **k-е элементы**
   - [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
   - [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)
   - [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)

3. **Объединение и слияние**
   - [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)
   - [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)
   - [632. Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/)

4. **Планирование**
   - [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/)
   - [502. IPO](https://leetcode.com/problems/ipo/)
   - [1834. Single-Threaded CPU](https://leetcode.com/problems/single-threaded-cpu/)

5. **Другие применения**
   - [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)
   - [767. Reorganize String](https://leetcode.com/problems/reorganize-string/)
   - [1642. Furthest Building You Can Reach](https://leetcode.com/problems/furthest-building-you-can-reach/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Binary Heap](https://www.geeksforgeeks.org/binary-heap/)
- [CP-Algorithms - Binary Heap](https://cp-algorithms.com/data_structures/binary_heap.html)
