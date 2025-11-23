# Префиксное дерево (Trie)

## 📝 Описание
Trie (префиксное дерево) — это древовидная структура данных, которая используется для эффективного хранения и поиска строковых ключей.

## 🎯 Основные операции
- `insert`: O(m) - вставка строки длины m
- `search`: O(m) - поиск строки
- `starts_with`: O(m) - проверка префикса
- `delete`: O(m) - удаление строки

## 📋 Интерфейс
```cpp
class Trie {
    struct TrieNode {
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
        bool is_end_of_word = false;
    };
    
    std::unique_ptr<TrieNode> root;
    
public:
    Trie();
    void insert(const std::string& word);
    bool search(const std::string& word) const;
    bool starts_with(const std::string& prefix) const;
    void remove(const std::string& word);
    std::vector<std::string> get_words_with_prefix(const std::string& prefix) const;
};
```

## 📌 15 фундаментальных задач
1. **Базовые операции**
   - [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)
   - [211. Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/)
   - [720. Longest Word in Dictionary](https://leetcode.com/problems/longest-word-in-dictionary/)

2. **Поиск и автодополнение**
   - [1268. Search Suggestions System](https://leetcode.com/problems/search-suggestions-system/)
   - [642. Design Search Autocomplete System](https://leetcode.com/problems/design-search-autocomplete-system/)
   - [676. Implement Magic Dictionary](https://leetcode.com/problems/implement-magic-dictionary/)

3. **Поиск слов**
   - [212. Word Search II](https://leetcode.com/problems/word-search-ii/)
   - [472. Concatenated Words](https://leetcode.com/problems/concatenated-words/)
   - [648. Replace Words](https://leetcode.com/problems/replace-words/)

4. **Специальные структуры**
   - [745. Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/)
   - [1032. Stream of Characters](https://leetcode.com/problems/stream-of-characters/)
   - [820. Short Encoding of Words](https://leetcode.com/problems/short-encoding-of-words/)

5. **Дополнительные задачи**
   - [677. Map Sum Pairs](https://leetcode.com/problems/map-sum-pairs/)
   - [588. Design In-Memory File System](https://leetcode.com/problems/design-in-memory-file-system/)
   - [642. Design Search Autocomplete System](https://leetcode.com/problems/design-search-autocomplete-system/)

## 🔗 Полезные ссылки
- [GeeksforGeeks - Trie Data Structure](https://www.geeksforgeeks.org/trie-insert-and-search/)
- [CP-Algorithms - Trie](https://cp-algorithms.com/string/trie.html)
