namespace fft {

using Complex = std::complex<double>;

const double kPi = std::acos(-1.0);
constexpr int kLogN = 19;
constexpr int kMaxN = 1 << kLogN;

bool g_is_inited = false;

Complex rootw[kMaxN];
Complex dp[kMaxN];
int logn[kMaxN];
int rev[kMaxN];

void Init() {
    rootw[0] = 1;
    logn[0] = -1;
    auto root = Complex(std::cos(kPi / (kMaxN >> 1)), std::sin(kPi / (kMaxN >> 1)));
    for (int i = 1; i < kMaxN; ++i) {
        rootw[i] = rootw[i - 1] * root;
        logn[i] = logn[i >> 1] + 1;
        rev[i] = rev[i ^ (1 << logn[i])] | (1 << (kLogN - logn[i] - 1));
    }
    for (int i = 3; i < kMaxN; ++i) {
        logn[i] += (i & (i - 1)) != 0;
    }
    g_is_inited = true;
}

void FFT(std::vector<Complex>& arr, int power) {
    const int size = 1 << power;
    for (int i = 0; i < size; ++i) {
        dp[rev[i] >> (kLogN - power)] = arr[i];
    }
    for (int d = 0; d < power; ++d) {
        const int len = 1 << d;
        for (int i = 0; i < size; i += len << 1) {
            for (int j = 0; j < len; ++j) {
                auto delta = dp[i + len + j] * rootw[j << (kLogN - d - 1)];
                dp[i + len + j] = dp[i + j] - delta;
                dp[i + j] += delta;
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        arr[i] = dp[i];
    }
}

std::vector<int> Multiply(const std::vector<int>& first, const std::vector<int>& second) {
    if (!g_is_inited) {
        Init();
    }
    const int power = logn[std::max(first.size(), second.size())] + 1;
    const int len = 1 << power;
    std::vector<Complex> aa(first.begin(), first.end());
    for (int i = 0; i < len - (int)first.size(); ++i) {
        aa.emplace_back(0);
    }
    std::vector<Complex> bb(second.begin(), second.end());
    for (int i = 0; i < len - (int)second.size(); ++i) {
        bb.emplace_back(0);
    }
    FFT(aa, power);
    FFT(bb, power);
    for (int i = 0; i < len; ++i) {
        aa[i] *= bb[i];
    }
    FFT(aa, power);
    std::vector<int> res(len);
    for (int i = 0; i < len; ++i) {
        res[i] = int(aa[i].real() / len + 0.5);
    }
    std::reverse(std::next(res.begin()), res.end());
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    return res;
}

}  // namespace fft
