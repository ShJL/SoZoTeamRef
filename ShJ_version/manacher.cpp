Notes:
    - cnt_odd[i] - кол-во палиндромов с центром в i
    - cnt_even[i] - кол-во палиндромов, где i начало второй половины
-------------------------------------------------------------------------

int cnt_even[100000];
int cnt_odd[100000];

void Manacher(const string& s) {
    const int n = size(s);
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
        int k = 1;
        if (i < r) {
            k = min(r - i + 1, cnt_odd[l + r - i]);
        }
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            ++k;
        }
        cnt_odd[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        int k = 0;
        if (i < r) {
            k = min(r - i + 1, cnt_even[l + r - i + 1]);
        }
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            ++k;
        }
        cnt_even[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k;
        }
    }
}
