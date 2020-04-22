constexpr int MAXN = 200000;

vector<int> gr[MAXN];
int tsize[MAXN];
int level[MAXN];

void GetSize(int from, int p = -1) {
    tsize[from] = 1;
    for (int to : gr[from]) {
        if (to != p && level[to] == -1) {
            GetSize(to, from);
            tsize[from] += tsize[to];
        }
    }
}

pair<int, int> GetCentroid(int from, int n, int p = -1) {
    for (int to : gr[from]) {
        if (to != p && level[to] == -1 && tsize[to] + tsize[to] > n) {
            return GetCentroid(to, n, from);
        }
    }
    return {from, p};
}

void Build(int from, int lvl) {
    auto [centroid, centroid_prnt] = GetCentroid(from, tsize[from]);
    level[centroid] = lvl;
    // prnt[centroid] = prev_centroid;  // построение дерева центройдов
    // здесь может быть обработка компоненты центром в центройде
    for (int to : gr[centroid]) {
        if (level[to] == -1) {
            if (to == centroid_prnt) {
                GetSize(to);
            }
            Build(to, lvl + 1);
        }
    }
}

void CentroidDecomp(int n) {
    memset(level, -1, sizeof(int) * n);
    GetSize(0);
    Build(0, 0);
}
