# Граф (Graph)

## 📝 Описание
Граф - это структура данных, состоящая из вершин и рёбер, соединяющих пары вершин.

## 🎯 Основные операции
- `add_vertex`: O(1) - добавление вершины
- `add_edge`: O(1) - добавление ребра
- `remove_vertex`: O(V + E) - удаление вершины
- `remove_edge`: O(1) - удаление ребра
- `are_adjacent`: O(1) - проверка смежности

## 📋 Интерфейс
```cpp
class Graph {
    using AdjList = std::unordered_map<int, std::vector<int>>;
    AdjList adj_list;
    
public:
    void add_vertex(int v);
    void add_edge(int v1, int v2);
    void remove_vertex(int v);
    void remove_edge(int v1, int v2);
    bool are_adjacent(int v1, int v2) const;
    const std::vector<int>& get_neighbors(int v) const;
    size_t vertex_count() const;
    size_t edge_count() const;
};
```

## 📌 15 фундаментальных задач
1. **Обход в глубину (DFS)**
   - [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
   - [133. Clone Graph](https://leetcode.com/problems/clone-graph/)
   - [207. Course Schedule](https://leetcode.com/problems/course-schedule/)

2. **Обход в ширину (BFS)**
   - [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
   - [127. Word Ladder](https://leetcode.com/problems/word-ladder/)
   - [542. 01 Matrix](https://leetcode.com/problems/01-matrix/)

3. **Кратчайший путь**
   - [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)
   - [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
   - [1334. Find the City With the Smallest Number of Neighbors](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors/)

4. **Минимальное остовное дерево**
   - [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)
   - [1135. Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/)

5. **Топологическая сортировка**
   - [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
   - [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)

6. **Эйлеров путь**
   - [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)
   - [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Graph Data Structure](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/)
