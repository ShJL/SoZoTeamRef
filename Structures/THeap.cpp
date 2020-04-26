template <int SIZE, typename T, bool Min = true>
class THeap {
private:
    T Array_[SIZE];
    int Counter_ = 0;

    inline int Parent(int x) __attribute__((always_inline)) {
        return (x - 1) >> 1;
    }

    inline int Left(int x) __attribute__((always_inline)) {
        return (x << 1) + 1;
    }

    inline int Right(int x) __attribute__((always_inline)) {
        return (x << 1) + 2;
    }

    inline void Swap(T &a, T &b) __attribute__((always_inline)) {
        T c = std::move(a);
        a = std::move(b);
        b = std::move(c);
    }

    inline void RankUp() __attribute__((always_inline)) {
        int i = Counter_;
        if constexpr (Min) {
            while (i && Array_[Parent(i)] > Array_[i]) {
                Swap(Array_[Parent(i)], Array_[i]);
                i = Parent(i);
            }
        } else {
            while (i && Array_[Parent(i)] < Array_[i]) {
                Swap(Array_[Parent(i)], Array_[i]);
                i = Parent(i);
            }
        }
    }

    inline void RankDown() __attribute__((always_inline)) {
        if (Counter_ == 0)
            return;
        Counter_--;
        Swap(Array_[0], Array_[Counter_]);
        int i = 0;
        if constexpr (Min) {
            while (Left(i) < Counter_) {
                if (Right(i) < Counter_) {
                    if (Array_[i] < Array_[Left(i)] && Array_[i] < Array_[Right(i)]) {
                        break;
                    }
                    if (Array_[Left(i)] < Array_[Right(i)]) {
                        Swap(Array_[Left(i)], Array_[i]);
                        i = Left(i);
                    } else {
                        Swap(Array_[Right(i)], Array_[i]);
                        i = Right(i);
                    }
                } else if (Left(i) < Counter_) {
                    if (Array_[Left(i)] < Array_[i]) {
                        Swap(Array_[Left(i)], Array_[i]);
                        i = Left(i);
                    } else {
                        break;
                    }
                }
            }
        } else {
            while (Left(i) < Counter_) {
                if (Right(i) < Counter_) {
                    if (Array_[i] > Array_[Left(i)] && Array_[i] > Array_[Right(i)]) {
                        break;
                    }
                    if (Array_[Left(i)] > Array_[Right(i)]) {
                        Swap(Array_[Left(i)], Array_[i]);
                        i = Left(i);
                    } else {
                        Swap(Array_[Right(i)], Array_[i]);
                        i = Right(i);
                    }
                } else if (Left(i) < Counter_) {
                    if (Array_[Left(i)] > Array_[i]) {
                        Swap(Array_[Left(i)], Array_[i]);
                        i = Left(i);
                    } else {
                        break;
                    }
                }
            }
        }
    }

public:
    void Push(T value) {
        Array_[Counter_] = value;
        RankUp();
        Counter_++;
    }
    T Pop() {
        T result = Array_[0];
        RankDown();
        return result;
    }
    T Peek() const {
        return Array_[0];
    }
    int Size() const {
        return Counter_;
    }
};

// EXAMPLE

using namespace std;

int main() {
    const int n = 100;
    THeap<n, double, false> maxHeap;
    for (int i = 0; i < n; i++) {
        maxHeap.Push(rand() * 1.0 / RAND_MAX);
    }
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(15) << maxHeap.Pop() << endl;
    }
}
