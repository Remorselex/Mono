# Бинарное дерево поиска (BST)

## 📝 Описание
Бинарное дерево поиска - это дерево, где для каждого узла:
- Все узлы левого поддерева содержат значения меньше корня
- Все узлы правого поддерева содержат значения больше корня
- Оба поддерева также являются BST

## 🎯 Основные операции
- `insert`: O(h) - вставка элемента
- `search`: O(h) - поиск элемента
- `delete`: O(h) - удаление элемента
- `traversal`: O(n) - обход дерева
где h - высота дерева (в сбалансированном дереве h = log n)

## 📋 Интерфейс
```cpp
template <typename T>
class BinarySearchTree {
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    
    Node* root_;
    
public:
    void insert(const T& value);
    bool search(const T& value) const;
    void remove(const T& value);
    
    // Обходы
    void in_order(std::function<void(T)> visit) const;
    void pre_order(std::function<void(T)> visit) const;
    void post_order(std::function<void(T)> visit) const;
    
    // Вспомогательные методы
    bool is_bst() const;
    int height() const;
    T min() const;
    T max() const;
};
```

## 📌 15 фундаментальных задач
1. **Базовые операции**
   - [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)
   - [700. Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)
   - [701. Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/)

2. **Обходы и преобразования**
   - [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
   - [108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)
   - [109. Convert Sorted List to Binary Search Tree](https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/)

3. **Модификации BST**
   - [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/)
   - [669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)
   - [1382. Balance a Binary Search Tree](https://leetcode.com/problems/balance-a-binary-search-tree/)

4. **Свойства BST**
   - [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)
   - [235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)
   - [653. Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/)

5. **Дополнительные задачи**
   - [99. Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/)
   - [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/)
   - [538. Convert BST to Greater Tree](https://leetcode.com/problems/convert-bst-to-greater-tree/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Binary Search Tree](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
