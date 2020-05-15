#define X first
#define Y second
using pii = std::pair<int, int>;

pii Vector(pii head, pii tail) {
    return {tail.X - head.X, tail.Y - head.Y};
}

long long Cross(pii lhs, pii rhs) {
    return 1LL * lhs.X * rhs.Y - 1LL * lhs.Y * rhs.X;
}

vector<pii> ConvexHull(vector<pii>& vec) {
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    if (vec.size() == 1) {
        return vec;
    }
    const pii pleft = vec.front();
    const pii pright = vec.back();
    vector<pii> up{pleft};
    vector<pii> down{pleft};
    for (int i = 1; i < sz(vec); ++i) {
        const long long cp = Cross(Vector(pleft, vec[i]), Vector(vec[i], pright));
        if (cp < 0 || i + 1 == sz(vec)) {
            while (down.size() > 1 && Cross(Vector(up[up.size() - 2], vec[i]), Vector(up[up.size() - 2], up.back())) <= 0) {
                up.pop_back();
            }
            up.push_back(vec[i]);
        }
        if (cp > 0 || i + 1 == sz(vec)) {
            while (down.size() > 1 && Cross(Vector(down[down.size() - 2], vec[i]), Vector(down[down.size() - 2], down.back())) >= 0) {
                down.pop_back();
            }
            down.push_back(vec[i]);
        }
    }
    down.insert(down.end(), next(up.rbegin()), prev(up.rend()));
    return down;
}
