template <typename T, bool Min = true>
class TMinMaxQueue {
private:
    std::queue<T> Queue_;
    std::deque<std::pair<T, int>> Deque_;
    int Counter_ = 0;
    int CounterDeleted_ = 0;
    const std::string EMPTY_QUEUE_ERROR = "EMPTY QUEUE EXCEPTION";

public:
    void Push(T x) {
        if constexpr (Min) {
            while (!Deque_.empty() && Deque_.back().first <= x) {
                Deque_.pop_back();
            }
        } else {
            while (!Deque_.empty() && Deque_.back().first <= x) {
                Deque_.pop_back();
            }
        }
        Deque_.emplace_back(x, Counter_++);
        Queue_.push(x);
    }

    T Max() const {
        if (Queue_.empty()) {
            throw EMPTY_QUEUE_ERROR;
        }
        return Deque_.front().first;
    }

    void Pop() {
        if (Queue_.empty()) {
            throw EMPTY_QUEUE_ERROR;
        }
        if (Deque_.front().second == CounterDeleted_) {
            Deque_.pop_front();
        }
        CounterDeleted_++;
        Queue_.pop();
    }

    T Peek() const {
        return Queue_.front();
    }
};

// EXAMPLE

using namespace std;

int main() {
    const int n = 12;
    TMinMaxQueue<int, true> minQueue;
    for (int i = 0; i < n; i++) {
        int tmp = n - i;
        minQueue.Push(tmp);
        cout << tmp << ' ';
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << minQueue.Max() << ' ' << minQueue.Peek() << endl;
        minQueue.Pop();
    }

}
