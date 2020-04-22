int AddMod(int x, int y, int mod) {
    x += y;
    return x < mod ? x : x - mod;
}

int SubMod(int x, int y, int mod) {
    x -= y;
    return x >= 0 ? x : x + mod;
}

vector<int> BuildSuffArr(string s) {
    const int alphabet_size = 128;
    s.push_back('\0');
    const int n = s.size();
    vector<int> cnt(max(alphabet_size, n), 0);
    for (auto c : s) {
        ++cnt[c];
    }
    for (int i = 1; i < alphabet_size; ++i) {
        cnt[i] += cnt[i - 1];
    }
    vector<int> suff_arr(n);
    for (int i = 0; i < n; ++i) {
        suff_arr[--cnt[s[i]]] = i;
    }
    vector<vector<int>> cls(2, vector<int>(n, 0));
    int cur = 0;
    int cnt_cls = 1;
    for (int i = 1; i < n; ++i) {
        if (s[suff_arr[i]] != s[suff_arr[i - 1]]) {
            ++cnt_cls;
        }
        cls[cur][suff_arr[i]] = cnt_cls - 1;
    }
    vector<int> perm_sa(n);
    for (int len = 1; len < n; len <<= 1) {
        int pre = cur;
        cur ^= 1;
        fill_n(cnt.begin(), cnt_cls, 0);
        for (int i = 0; i < n; ++i) {
            perm_sa[i] = SubMod(suff_arr[i], len, n);
            ++cnt[cls[pre][i]];
        }
        for (int i = 1; i < cnt_cls; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            suff_arr[--cnt[cls[pre][perm_sa[i]]]] = perm_sa[i];
        }
        cls[cur][suff_arr[0]] = 0;
        cnt_cls = 1;
        for (int i = 1; i < n; ++i) {
            if (cls[pre][suff_arr[i]] != cls[pre][suff_arr[i - 1]] ||
                cls[pre][AddMod(suff_arr[i], len, n)] != cls[pre][AddMod(suff_arr[i - 1], len, n)])
            {
                ++cnt_cls;
            }
            cls[cur][suff_arr[i]] = cnt_cls - 1;
        }
    }
    suff_arr.erase(suff_arr.begin());
    return suff_arr;
}

vector<int> BuildLCP(const string& s, const vector<int>& suff_arr) {
    const int n = s.size();
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[suff_arr[i]] = i;
    }
    vector<int> lcp(n - 1);
    for (int i = 0, k = 0; i < n; ++i) {
        if (pos[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suff_arr[pos[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[pos[i]] = k;
        if (k != 0) {
            --k;
        }
    }
    return lcp;
}
