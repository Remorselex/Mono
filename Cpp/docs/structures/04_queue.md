# Очередь (Queue)

## 📝 Описание
Очередь - это структура данных, работающая по принципу FIFO (First In, First Out).

## 🎯 Основные операции
- `enqueue`: O(1) - добавление элемента в конец
- `dequeue`: O(1) - удаление из начала
- `front`: O(1) - первый элемент
- `is_empty`: O(1) - проверка на пустоту

## 📋 Интерфейс
```cpp
template <typename T>
class Queue {
public:
    void enqueue(const T& value);
    void dequeue();
    T& front();
    const T& front() const;
    bool empty() const;
    size_t size() const;
};
```

## 📌 15 фундаментальных задач
1. **Базовые задачи**
   - [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
   - [346. Moving Average from Data Stream](https://leetcode.com/problems/moving-average-from-data-stream/)
   - [933. Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)

2. **BFS и обходы**
   - [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
   - [103. Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
   - [127. Word Ladder](https://leetcode.com/problems/word-ladder/)

3. **Очереди с приоритетом**
   - [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
   - [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)
   - [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)

4. **Дек и двусторонняя очередь**
   - [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
   - [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)
   - [1425. Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)

5. **Дополнительные задачи**
   - [622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
   - [641. Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)
   - [1670. Design Front Middle Back Queue](https://leetcode.com/problems/design-front-middle-back-queue/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Queue Data Structure](https://www.geeksforgeeks.org/queue-data-structure/)
