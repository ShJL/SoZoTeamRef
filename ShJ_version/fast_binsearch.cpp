// [lo, hi)

int lo = ...;
int hi = ...;
while (lo < hi) {
    int mid = (lo + hi) >> 1;
    if (...) {
        hi = mid;  // lo = mid + 1;
    } else {
        lo = mid + 1;  // hi = mid;
    }
}

