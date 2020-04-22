Notes:
    n - размер первой доли
    mt - v(2) -> v(1)
-------------------------------------------------------------

constexpr int MAXN = 250;

vector<int> gr[MAXN];
int used[MAXN];
int USED = 1;
int mt[MAXN];

bool Kuhn(int from) {
    used[from] = USED;
    for (int to : gr[from]) {
        if (mt[to] == -1) {
            mt[to] = from;
            return true;
        }
    }
    for (int to : gr[from]) {
        if (used[mt[to]] != USED && Kuhn(mt[to])) {
            mt[to] = from;
            return true;
        }
    }
    return false;
}

int Matching(int n) {
    memset(mt, -1, sizeof(mt));
    int res = 0;
    for (int v = 0; v < n; ++v) {
        if (used[v] != USED && Kuhn(v)) {
            ++res;
            ++USED;
        }
    }
    return res;
}