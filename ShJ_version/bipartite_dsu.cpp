Note:
    - dsu для сливания множеств и поддержания в них двух классов и их размеров
    - flag используется для выбора одного класса
-------------------------------------------------------------

class DSU {
public:
    explicit DSU(int n)
        : flag(n, -1), prnt(n), size(n, vector<int>(2, 0)), type(n, 0), verts(n) {
        iota(all(prnt), 0);
        loop(n) {
            size[i][0] = 1;
            verts[i].push_back(i);
        }
    }

    int Find(int v) {
        if (v == prnt[v]) {
            return v;
        }
        return prnt[v] = Find(prnt[v]);
    }

    int Cost(int v) {
        v = Find(v);
        if (flag[v] == -1) {
            return min(size[v][0], size[v][1]);
        }
        return size[v][flag[v]];
    }

    void SetFlag(int v, bool bad) {
        const int p = Find(v);
        res -= Cost(p);
        flag[p] = type[v] ^ bad;
        res += Cost(p);
    }

    void Union(int v, int u, bool diff) {
        const int fl = (type[v] != type[u]) ^ diff;
        u = Find(u);
        v = Find(v);
        if (u == v) {
            return;
        }
        res -= Cost(v) + Cost(u);
        if (sz(verts[u]) > sz(verts[v])) {
            swap(u, v);
        }
        if (flag[v] == -1 && flag[u] != -1) {
            flag[v] = flag[u] ^ fl;
        }
        size[v][0] += size[u][fl];
        size[v][1] += size[u][fl ^ 1];
        for (int x : verts[u]) {
            type[x] ^= fl;
        }
        prnt[u] = v;
        verts[v].insert(verts[v].end(), all(verts[u]));
        res += Cost(v);
    }

    int MinCount() const {
        return res;
    }

private:
    vector<int> flag;
    vector<int> prnt;
    vector<vector<int>> size;
    vector<int> type;
    vector<vector<int>> verts;
    int res = 0;
};
