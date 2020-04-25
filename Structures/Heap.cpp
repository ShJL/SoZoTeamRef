template<int SIZE, typename T, bool Min = true>
class Heap {
private:
    T arr[SIZE];
    int itr = 0;

    inline int par(int x) __attribute__((always_inline)) {
        return (x - 1) >> 1;
    }

    inline int left(int x) __attribute__((always_inline)) {
        return (x << 1) + 1;
    }

    inline int right(int x) __attribute__((always_inline)) {
        return (x << 1) + 2;
    }

    inline void Swap(T& a, T& b) __attribute__((always_inline)) {
        T c = std::move(a);
        a = std::move(b);
        b = std::move(c);
    }

    inline void RankUp() __attribute__((always_inline)) {
        int i = itr;
        if constexpr (Min) {
            while (i && arr[par(i)] > arr[i]) {
                Swap(arr[par(i)], arr[i]);
                i = par(i);
            }
        } else {
            while (i && arr[par(i)] < arr[i]) {
                Swap(arr[par(i)], arr[i]);
                i = par(i);
            }
        }
    }

    inline void RankDown() __attribute__((always_inline)) {
        if (itr == 0) return;
        itr--;
        Swap(arr[0], arr[itr]);
        int i = 0;
        if constexpr (Min) {
            while (left(i) < itr) {
                if (right(i) < itr) {
                    if (arr[i] < arr[left(i)] && arr[i] < arr[right(i)]) {
                        break;
                    }
                    if (arr[left(i)] < arr[right(i)]) {
                        Swap(arr[left(i)], arr[i]);
                        i = left(i);
                    } else {
                        Swap(arr[right(i)], arr[i]);
                        i = right(i);
                    }
                } else if (left(i) < itr) {
                    if (arr[left(i)] < arr[i]) {
                        Swap(arr[left(i)], arr[i]);
                        i = left(i);
                    } else {
                        break;
                    }
                }
            }
        } else {
            while (left(i) < itr) {
                if (right(i) < itr) {
                    if (arr[i] > arr[left(i)] && arr[i] > arr[right(i)]) {
                        break;
                    }
                    if (arr[left(i)] > arr[right(i)]) {
                        Swap(arr[left(i)], arr[i]);
                        i = left(i);
                    } else {
                        Swap(arr[right(i)], arr[i]);
                        i = right(i);
                    }
                } else if (left(i) < itr) {
                    if (arr[left(i)] > arr[i]) {
                        Swap(arr[left(i)], arr[i]);
                        i = left(i);
                    } else {
                        break;
                    }
                }
            }
        }
    }

public:
    void push(T value) {
        arr[itr] = value;
        RankUp();
        itr++;
    }
    T pop() {
        if (itr == 0) {
            throw "NO ELEMENTS EXCEPTION";
        }
        T result = arr[0];
        RankDown();
        return result;
    }
    int size() const {
        return itr;
    }
};

// EXAMPLE 

int main() {
    const int n = 100;
    Heap<n, double, false> maxHeap;
    for (int i = 0; i < n; i++) {
        maxHeap.push(rand() * 1.0 / RAND_MAX);
    }
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(15) << maxHeap.pop() << endl;
    }
}
