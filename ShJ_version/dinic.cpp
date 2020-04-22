Note:
    нахождение минимального разреза - пройти из истока по ребрам с CAP > FLOW,
                                      ребра с разными пометками на концах - разрез.
---------------------------------------------------------------------------------

using Long = int64_t;

class Dinic {
public:
    static constexpr Long kInf = 1e18;

    struct Edge {
        Long cap;
        Long flow = 0;
        int to;

        Edge(int tov, Long capacity) : cap(capacity), to(tov) {
        }
    };

    explicit Dinic(int nn) : gr(nn), dist(nn), ptr(nn) {
    }

    void AddEdge(int from, int to, Long cap) {
        if (from == to) {
            return;
        }
        gr[from].push_back((int)edges.size());
        edges.emplace_back(to, cap);
        gr[to].push_back((int)edges.size());
        edges.emplace_back(from, 0);
    }

    Long MaxFlow(int sv, int tv) {
        Long res = 0;
        while (Bfs(sv, tv)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (Long add = Dfs(sv, tv, kInf)) {
                res += add;
            }
        }
        return res;
    }

private:
    bool Bfs(int sv, int tv) {
        std::fill(dist.begin(), dist.end(), -1);
        dist[sv] = 0;
        que.push(sv);
        while (!que.empty()) {
            const int from = que.front();
            que.pop();
            for (int i : gr[from]) {
                if (dist[edges[i].to] == -1 && edges[i].cap > edges[i].flow) {
                    dist[edges[i].to] = dist[from] + 1;
                    que.push(edges[i].to);
                }
            }
        }
        return dist[tv] != -1;
    }

    Long Dfs(int from, int tv, Long pushed) {
        if (pushed == 0 || from == tv) {
            return pushed;
        }
        for (int& iter = ptr[from]; iter < (int)gr[from].size(); ++iter) {
            auto& ee = edges[gr[from][iter]];
            if (dist[ee.to] == dist[from] + 1 && ee.cap > ee.flow) {
                Long cur = Dfs(ee.to, tv, std::min(pushed, ee.cap - ee.flow));
                if (cur == 0) {
                    continue;
                }
                ee.flow += cur;
                edges[gr[from][iter] ^ 1].flow -= cur;
                return cur;
            }
        }
        return 0;
    }

    std::vector<Edge> edges;
    std::vector<std::vector<int>> gr;
    std::vector<int> dist;
    std::vector<int> ptr;
    std::queue<int> que;
};