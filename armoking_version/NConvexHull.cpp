namespace NConvexHull {
struct pt {
    ll x, y;
    pt(ll x, ll y) : x(x), y(y) {}
    pt operator + (const pt& o) {
        return pt{x + o.x, y + o.y};
    }
    pt operator - (const pt& o) const {
        return pt{x - o.x, y - o.y};
    }
    ll operator * (const pt& o) const {
        return x * o.x + y * o.y;
    }
    bool operator < (const pt& o) const {
        return x < o.x || x == o.x && y < o.y;
    }
    bool operator == (const pt& o) const {
        return x == o.x && y == o.y;
    }
};
 
ll cw(const pt& a, const pt& b) {
    return a.x * b.y - a.y * b.x;
}
 
ll norm(const pt& a) {
    return a.x * a.x + a.y * a.y;
}
 
vector<pt> ConvexHull (vector<pt> arr) {
    sort(all(arr));
    arr.erase(unique(all(arr)), arr.end());
    sort(arr.begin() + 1, arr.end(), [&] (const pt& a, const pt& b) {
        ll val = cw(a - arr[0], b - arr[0]);
        if (val != 0) return val < 0;
        return norm(a - arr[0]) < norm(b - arr[0]);
    });
    const int n = arr.size();
    if (n <= 2) return arr;
    vector<pt> ans = {arr[0], arr[1]};
    int sz = 2;
    for (int i = 2; i < n; i++) {
        while (sz >= 2 && cw(ans[sz - 1] - ans[sz - 2], arr[i] - ans[sz - 1]) >= 0) {
            ans.pop_back();
            sz--;
        }
        sz++;
        ans.push_back(arr[i]);
    }
    while (sz >= 2 && cw(ans[sz - 1] - ans[sz - 2], ans[0] - ans[sz - 1]) >= 0) {
        ans.pop_back();
        sz--;
    }
    return ans;
}
};
