class NodeTrie {
public:
    NodeTrie* nodes[26] = {};
    bool isEnd = false;
    int cnt = 0; // Counts how many words pass through this node (prefix count)
};

class Trie {
    NodeTrie* root;
public:
    Trie() { root = new NodeTrie(); }

    void insert(const string& word) {
        NodeTrie* node = root;
        node->cnt++;  
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->nodes[idx]) node->nodes[idx] = new NodeTrie();
            node = node->nodes[idx];
            node->cnt++;
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        NodeTrie* node = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!node->nodes[idx]) return false;
            node = node->nodes[idx];
        }
        return node->isEnd;
    }

    int prefixCount(const string& prefix) {
        NodeTrie* node = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (!node->nodes[idx]) return 0;
            node = node->nodes[idx];
        }
        return node->cnt;
    }
};