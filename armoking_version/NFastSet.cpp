namespace NFastSet {
template<size_t Words>
struct FastBitset : public _Base_bitset<Words> {
    const static int bit = log2(sizeof(unsigned long) * 8);
    FastBitset(unsigned long val = 0)
        : _Base_bitset<Words>(val)
    {
    }
    void insert(size_t index) {
        (this->_M_w[this->_S_whichword(index)]) |= this->_S_maskbit(index);
    }
    void flip(size_t index) {
        (this->_M_w[this->_S_whichword(index)]) ^= this->_S_maskbit(index);
    }
    bool contains(size_t index) const {
        return (this->_M_w[this->_S_whichword(index)] & (this->_S_maskbit(index))) != 0;
    }
    size_t upper_bound(size_t index, size_t border = Words * (1ULL << bit)) const {
        return this->_M_do_find_next(index, border);
    }
    size_t lower_bound(size_t index, size_t border = Words * (1ULL << bit)) const {
        if (contains(index)) {
            return index;
        }
        return upper_bound(index, border);
    }
    size_t begin() const {
        return this->_M_do_find_first(Words * (1ULL << bit));
    }
    unsigned long GetWordByIndex(size_t index) {
        return this->_M_getword(index);
    }
};

template<int N>
struct FastSet {
    const static int bit = log2(sizeof(unsigned long) * 8);
    const static int bit2 = bit * 2;
    const static int bit3 = bit * 3;
    const static size_t N0 = N + 2;
    const static size_t N1 = (N >> bit) + 2;
    const static size_t N2 = (N >> bit2) + 2;
    const static size_t N3 = (N >> bit3) + 2;

    FastBitset<N0> table0;
    FastBitset<N1> table1;
    FastBitset<N2> table2;
    FastBitset<N3> table3;

    FastSet()
        : table0(0)
        , table1(0)
        , table2(0)
        , table3(0)
    {}

    void insert(size_t index) {
        table0.insert(index);
        table1.insert(index >> bit);
        table2.insert(index >> bit2);
        table3.insert(index >> bit3);
    }

    void erase(size_t index) {
        if (contains(index)) {
            table0.flip(index);

            if (table0.GetWordByIndex(index) == 0UL) {
                int val = (index >> bit);
                table1.flip(index >> bit);

                if (table1.GetWordByIndex(index >> bit) == 0UL) {
                    table2.flip(index >> bit2);

                    if (table2.GetWordByIndex(index >> bit2) == 0UL) {
                        table3.flip(index >> bit3);
                    }
                }
            }
        }
    }

    bool contains(size_t index) {
        return table0.contains(index);
    }

    size_t lower_bound(size_t index) {
        if (contains(index)) return index;
        return lower_bound3(index, N + (1ULL << bit3));
    }

    size_t upper_bound(size_t index) {
        return lower_bound(index + 1);
    }

    size_t lower_bound3(size_t index, size_t border) {
        size_t current_index = table3.lower_bound(index >> bit3, (border >> bit3));
        if (current_index == (border >> bit3)) return border;
        if (current_index > (index >> bit3)) return lower_bound2(current_index << bit3, border);

        size_t current_border = (1 + (index >> bit3)) << bit3;
        size_t result = lower_bound2(index, current_border);
        if (result < current_border) return result;


        current_index = table3.upper_bound(current_index, (border >> bit3));
        if (current_index == (border >> bit3)) return border;

        return lower_bound2(current_index << bit3, border);
    }

    size_t lower_bound2(size_t index, size_t border) {
        size_t current_index = table2.lower_bound(index >> bit2, (border >> bit2));
        if (current_index == (border >> bit2)) return border;
        if (current_index > (index >> bit2)) return lower_bound1(current_index << bit2, border);

        size_t current_border = (1 + (index >> bit2)) << bit2;
        size_t result = lower_bound1(index, current_border);
        if (result < current_border) return result;

        current_index = table2.upper_bound(current_index, (border >> bit2));
        if (current_index == (border >> bit2)) return border;

        return lower_bound1(current_index << bit2, border);
    }


    size_t lower_bound1(size_t index, size_t border) {
        size_t current_index = table1.lower_bound(index >> bit, (border >> bit));
        if (current_index == (border >> bit)) return border;
        if (current_index > (index >> bit)) lower_bound0(current_index << bit, border);

        size_t current_border = (1 + current_index) << bit;
        size_t result = lower_bound0(index, current_border);
        if (result < current_border) return result;

        current_index = table1.upper_bound(current_index, (border >> bit));
        if (current_index == (border >> bit)) return border;

        return lower_bound0(current_index << bit, border);
    }


    size_t lower_bound0(size_t index, size_t border) {
        return table0.lower_bound(index, border);
    }
};

} // namespace NFastSet;
