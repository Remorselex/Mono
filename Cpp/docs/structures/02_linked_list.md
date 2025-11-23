# Связный список (Linked List)

## 📝 Описание
Связный список - это линейная структура данных, где каждый элемент (узел) содержит данные и указатель на следующий узел.

## 🎯 Основные операции

### 1. Вставка
- **В начало**: O(1)
- **В конец**: O(n) или O(1) с хранением tail
- **В середину**: O(n) (поиск позиции) + O(1) (вставка)

### 2. Удаление
- **С начала**: O(1)
- **С конца**: O(n)
- **Из середины**: O(n) (поиск) + O(1) (удаление)

### 3. Поиск
- **По значению**: O(n)
- **По индексу**: O(n)

## 📋 Интерфейс
```cpp
class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    
    Node* head_;
    Node* tail_;  // Опционально, для O(1) добавления в конец
    size_t size_;
    
public:
    LinkedList();
    ~LinkedList();
    
    // Основные операции
    void push_front(int value);
    void push_back(int value);
    void insert(size_t index, int value);
    void remove(size_t index);
    int at(size_t index) const;
    
    // Вспомогательные методы
    size_t size() const;
    bool empty() const;
    void clear();
    
    // Дополнительные методы
    void reverse();
    bool has_cycle() const;
    int find_middle() const;
};
```

## 🔍 Особенности реализации
1. **Односвязный список**:
   - Каждый узел содержит указатель только на следующий элемент
   - Вставка/удаление с начала за O(1)
   
2. **Двусвязный список**:
   - Каждый узел содержит указатели на следующий и предыдущий элементы
   - Удаление с конца за O(1)
   - Больше памяти на хранение указателей

## 📊 Сравнение с std::list
| Операция     | Наш LinkedList | std::list |
|--------------|----------------|-----------|
| Вставка в начало | O(1)     | O(1)      |
| Вставка в конец  | O(1)/O(n) | O(1)      |
| Удаление         | O(n)     | O(1)      |
| Доступ по индексу| O(n)     | O(n)      |
| Память на узел  | 1-2 указателя | 2 указателя |

## 📌 Рекомендуемые задачи
1. **Базовые операции**
   - [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
   - [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
   - [83. Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)

2. **Двухпоисковые задачи**
   - [141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
   - [142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
   - [160. Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)

3. **Разделение и объединение**
   - [86. Partition List](https://leetcode.com/problems/partition-list/)
   - [328. Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/)
   - [725. Split Linked List in Parts](https://leetcode.com/problems/split-linked-list-in-parts/)

4. **Сложные манипуляции**
   - [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)
   - [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/)
   - [61. Rotate List](https://leetcode.com/problems/rotate-list/)

5. **Дополнительные задачи**
   - [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)
   - [143. Reorder List](https://leetcode.com/problems/reorder-list/)
   - [148. Sort List](https://leetcode.com/problems/sort-list/)

## 🔗 Полезные ссылки
- [Википедия - Связный список](https://ru.wikipedia.org/wiki/Связный_список)
- [GeeksforGeeks - Linked List Data Structure](https://www.geeksforgeeks.org/data-structures/linked-list/)
