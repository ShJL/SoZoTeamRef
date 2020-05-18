template<typename T>
class TSparseTable {
private:
    int n, p;
    vector<vector<T>> table;
    vector<int> lg2;
public:
    void Operation(T& ans, T& left, T& right) {
        ans = max(left, right);
    }

    TSparseTable(const vector<T>& arr)
        : n(arr.size())
        , p(log2(n + 1) + 1)
        , table(p, vector<T>(n, 0))
    {
        table[0] = arr;
        for (int d = 1; d < p; d++) {
            int dlt = 1 << (d - 1);
            for (int i = 0; i + dlt < n; i++) {
                Operation(table[d][i], table[d - 1][i], table[d - 1][i + dlt]);
            }
        }
        lg2.resize(n + 1);
        lg2[0] = -1;
        for (int i = 1; i <= n; i++) {
            lg2[i] = lg2[i >> 1] + 1;
        }
    }

    T operator () (int l, int r) {
        if (l > r) return 0;
        int p = lg2[r - l + 1];
        static T answer;
        Operation(answer, table[p][l], table[p][r - (1 << p) + 1]);
        return answer;
    }
};
