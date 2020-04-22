template<int ASIZE, int AFIRST>
class Trie {
public:
    static constexpr int EMPTY = -1;

    struct Node {
        vector<int> Next;
        vector<int> Go;
        int SuffLink = 0;
        int NextTerm = EMPTY;
        vector<int> IsTerm;

        Node() : Next(ASIZE, EMPTY), Go(ASIZE, 0) {
        }
    };

    Trie() : trie(1) {
    }

    void Add(const string& s, int id) {
        int v = 0;
        for (char c : s) {
            const int i = c - AFIRST;
            if (trie[v].Next[i] == EMPTY) {
                trie[v].Next[i] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].Next[i];
        }
        trie[v].IsTerm.push_back(id);
    }

    void Build() {
        // suff_tree.resize(trie.size());
        queue<int> q;
        for (int i = 0; i < ASIZE; ++i) {
            if (trie[0].Next[i] != EMPTY) {
                trie[0].Go[i] = trie[0].Next[i];
                q.push(trie[0].Next[i]);
            }
        }
        while (!q.empty()) {
            const int v = q.front();
            q.pop();
            trie[v].NextTerm = !trie[trie[v].SuffLink].IsTerm.empty() ?  // suff link is term
                               trie[v].SuffLink : trie[trie[v].SuffLink].NextTerm;
            // suff_tree[trie[v].NextTerm != EMPTY ? trie[v].NextTerm : 0].push_back(v);
            for (int i = 0; i < ASIZE; ++i) {
                if (trie[v].Next[i] != EMPTY) {
                    trie[v].Go[i] = trie[v].Next[i];
                    trie[trie[v].Next[i]].SuffLink = trie[trie[v].SuffLink].Go[i];
                    q.push(trie[v].Next[i]);
                } else {
                    trie[v].Go[i] = trie[trie[v].SuffLink].Go[i];
                }
            }
        }
    }

    void Run(const string& s, vector<char>& res) {
        vector<char> used(trie.size(), false);
        int v = 0;
        for (char c : s) {
            v = trie[v].Go[c - AFIRST];
            for (int u = v; u != EMPTY && !used[u]; u = trie[u].NextTerm) {
                used[u] = true;
                for (int x : trie[u].IsTerm) {
                    res[x] = true;
                }
            }
        }
    }

private:
    vector<Node> trie;
    vector<vector<int>> suff_tree;
};