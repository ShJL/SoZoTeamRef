template< typename T, T (*Merge) (const T&, const T&) >
struct SegmentTree {
    T defaultValue;
    vector<T> t;

    SegmentTree(int n, T defaultValue = 0)
        : defaultValue(defaultValue)
        , t(n * 4, defaultValue)
    {}

    T Get(int v, int tl, int tr, int l, int r) {
        if (tl >= r || tr <= l) return defaultValue;
        if (tl >= l && tr <= r) return t[v];
        int tm = (tl + tr) >> 1;
        return Merge(Get(v * 2 + 1, tl, tm, l, r), Get(v * 2 + 2, tm, tr, l, r));
    }

    void Set(int v, int tl, int tr, int index, T value) {
        if (tl + 1 == tr) {
            t[v] = value;
        } else {
            int tm = (tl + tr) >> 1;
            if (index < tm) {
                Set(v * 2 + 1, tl, tm, index, value);
            } else {
                Set(v * 2 + 2, tm, tr, index, value);
            }
            t[v] = Merge(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

    void Add(int v, int tl, int tr, int index, T value) {
        if (tl + 1 == tr) {
            t[v] = Merge(t[v], value);
        } else {
            int tm = (tl + tr) >> 1;
            if (index < tm) {
                Add(v * 2 + 1, tl, tm, index, value);
            } else {
                Add(v * 2 + 2, tm, tr, index, value);
            }
            t[v] = Merge(t[v * 2 + 1], t[v * 2 + 2]);
        }
    }

    int LowerBound(int v, int tl, int tr, int l, int r, T value) {
        if (tl >= r || tr <= l || t[v] < value) return -1;
        if (tl + 1 == tr) {
            return tl;
        } else {
            int tm = (tl + tr) >> 1;
            int leftResult = LowerBound(v * 2 + 1, tl, tm, l, r, value);
            if (leftResult != -1) {
                return leftResult;
            } else {
                return LowerBound(v * 2 + 2, tm, tr, l, r, value);
            }
        }
    }

    int UpperBound(int v, int tl, int tr, int l, int r, T value) {
        if (tl >= r || tr <= l || t[v] <= value) return -1;
        if (tl + 1 == tr) {
            return tl;
        } else {
            int tm = (tl + tr) >> 1;
            int leftResult = UpperBound(v * 2 + 1, tl, tm, l, r, value);
            if (leftResult != -1) {
                return leftResult;
            } else {
                return UpperBound(v * 2 + 2, tm, tr, l, r, value);
            }
        }
    }

};

// EXAMPLE:

template<int MOD>
long long f(const long long& a, const long long& b) {
    return (a * b) % MOD;
}

int main() {
    const int n = 1e6 + 1;
    const int MOD = 1e9 + 7;

    SegmentTree<long long, f<MOD>> tree(n, 1);

    for (int i = 0; i < n; i++) {
        tree.Add(0, 0, n, i, i + 1);
    }

    cout << tree.Get(0, 0, n, 0, n) << endl;

}
