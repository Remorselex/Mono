# Стек (Stack)

## 📝 Описание
Стек - это структура данных, работающая по принципу LIFO (Last In, First Out).

## 🎯 Основные операции
- `push`: O(1) - добавление элемента
- `pop`: O(1) - удаление верхнего элемента
- `peek/top`: O(1) - просмотр верхнего элемента
- `is_empty`: O(1) - проверка на пустоту

## 📋 Интерфейс
```cpp
template <typename T>
class Stack {
public:
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    size_t size() const;
};
```

## 📌 15 фундаментальных задач
1. **Базовые задачи**
   - [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
   - [155. Min Stack](https://leetcode.com/problems/min-stack/)
   - [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)

2. **Польская нотация**
   - [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
   - [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)
   - [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)

3. **Задачи с вложенностью**
   - [394. Decode String](https://leetcode.com/problems/decode-string/)
   - [856. Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/)
   - [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/)

4. **Монотонный стек**
   - [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
   - [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
   - [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)

5. **Дополнительные задачи**
   - [316. Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/)
   - [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)
   - [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Stack Data Structure](https://www.geeksforgeeks.org/stack-data-structure/)
