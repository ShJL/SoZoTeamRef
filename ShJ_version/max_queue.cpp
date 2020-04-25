class MaxQueue {
public:
    struct Entity {
        int value = 0;
        int index = 0;

        Entity(int val, int ind) : value(val), index(ind) {
        }
    };

    void Pop() {
        if (queue_.front().index == cnt_removed_) {
            queue_.pop_front();
        }
        ++cnt_removed_;
    }

    void Push(int val) {
        while (!queue_.empty() && queue_.back().value <= val) {
            queue_.pop_back();
        }
        queue_.emplace_back(val, cnt_added_);
        ++cnt_added_;
    }

    int Max() const {
        return queue_.front().value;
    }

private:
    int cnt_added_ = 0;
    int cnt_removed_ = 0;
    std::deque<Entity> queue_;
};
