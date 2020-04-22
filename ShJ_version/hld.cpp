Note:
    - vid можно заменить, на массив с начальными занчениями в вершинах
---------------------------------------------------------------------------------------

using Graph = vector<vector<int>>;

class SegmentTree {
public:
    struct Node {
        int Val = 0;
    };

    explicit SegmentTree(int n) : size(n), tree(size << 2) {
    }

    void Update(int i, int x) {
        UpdateImpl(0, 0, size - 1, i, x);
    }

    int GetMax(int l, int r) {
        return QueryImpl(0, 0, size - 1, l, r);
    }

private:
    int Left(int v) const {
        return (v << 1) + 1;
    }

    int Right(int v) const {
        return (v << 1) + 2;
    }

    void UpdateVertex(int v) {
        tree[v].Val = max(tree[Left(v)].Val, tree[Right(v)].Val);
    }

    void UpdateImpl(int v, int tl, int tr, int i, int x) {
        if (tl == tr) {
            tree[v].Val += x;
            return;
        }
        int mid = (tl + tr) >> 1;
        if (i <= mid) {
            UpdateImpl(Left(v), tl, mid, i, x);
        } else {
            UpdateImpl(Right(v), mid + 1, tr, i, x);
        }
        UpdateVertex(v);
    }

    int QueryImpl(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return -INF;
        }
        if (tl == l && r == tr) {
            return tree[v].Val;
        }
        int mid = (tl + tr) >> 1;
        return max(QueryImpl(Left(v), tl, mid, l, min(mid, r)),
                   QueryImpl(Right(v), mid + 1, tr, max(mid + 1, l), r));
    }

    int size;
    vector<Node> tree;
};

class HLD {
public:
    explicit HLD(const Graph& gr)
        : chain(gr.size()), depth(gr.size(), 0), head(gr.size()), heavy(gr.size(), -1),
          num(gr.size()), prnt(gr.size()), tsize(gr.size()) {
        Dfs(gr, 0, 0);
        int vid = 0;
        Hld(gr, 0, 0, vid);
    }

    void Modify(int v, int x) {
        sts[chain[v]].Update(num[v], x);
    }

    int Query(int a, int b) {
        int res = -INF;
        while (chain[a] != chain[b]) {
            if (depth[head[chain[a]]] < depth[head[chain[b]]]) {
                swap(a, b);
            }
            res = max(res, sts[chain[a]].GetMax(0, num[a]));
            a = prnt[head[chain[a]]];
        }
        if (depth[a] > depth[b]) {
            swap(a, b);
        }
        res = max(res, sts[chain[a]].GetMax(num[a], num[b]));
        return res;
    }

private:
    void Dfs(const Graph& gr, int from, int p) {
        prnt[from] = p;
        tsize[from] = 1;
        for (int to : gr[from]) {
            if (to != p) {
                depth[to] = depth[from] + 1;
                Dfs(gr, to, from);
                tsize[from] += tsize[to];
                if (heavy[from] == -1 || tsize[to] > tsize[heavy[from]]) {
                    heavy[from] = to;
                }
            }
        }
    }

    void Hld(const Graph& gr, int from, int p, int& vid) {
        chain[from] = sts.size();
        num[from] = vid++;
        if (vid == 1) {
            head[chain[from]] = from;
        }
        if (heavy[from] != -1) {
            Hld(gr, heavy[from], from, vid);
        }
        if (vid > 0) {
            sts.emplace_back(vid);
            vid = 0;
        }
        for (int to : gr[from]) {
            if (to != p && to != heavy[from]) {
                Hld(gr, to, from, vid);
            }
        }
    }

    vector<int> chain;
    vector<int> depth;
    vector<int> head;
    vector<int> heavy;
    vector<int> num;
    vector<int> prnt;
    vector<int> tsize;
    vector<SegmentTree> sts;
};
