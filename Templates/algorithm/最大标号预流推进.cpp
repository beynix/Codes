struct Graph {
    static const int infty = 0x7f7f7f7f;
    struct edgetype {
        int to, next, flow, cap;
    };
    struct node {
        int u, d;
        bool operator < (const node& rhs) const {
            return d < rhs.d;
        }
    };
    int n, m, s, t;
    std::vector< edgetype > edge;
    std::vector< int > head, h, excess;
    std::priority_queue< node > Q;
    Graph() {
        n = m = 0;
        head.clear(); h.clear(); edge.clear(); excess.clear();
    }
    Graph(int n, int m) {
        this->n = n; this->m = m;
        head.resize(n + 1); h.resize(n + 1); excess.resize(n + 1);
        head.assign(n + 1, -1);
    }
    void AddEdge(int from, int to, int cap) {
        edge.push_back((edgetype){to, head[from], 0, cap});
        head[from] = edge.size() - 1;
        edge.push_back((edgetype){from, head[to], 0, 0});
        head[to] = edge.size() - 1;
    }
    void Push(int u, long long& maxflow) {
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            int f = min(edge[i].cap - edge[i].flow, excess[u]);
            if (f > 0 && (u == s || h[u] == h[v] + 1)) {
                edge[i].flow += f; edge[i ^ 1].flow -= f;
                excess[u] -= f; excess[v] += f;
                if (v == t) maxflow += f;
                else if (v != s) Q.push((node){v, h[v]});
            }
        }
    }
    void Relabel(int u) {
        if (u != s && u != t && excess[u] > 0) h[u]++, Q.push((node){u, h[u]}); 
    }
    long long Maxflow(int s, int t) {
        this->s = s; this->t = t;
        long long maxflow = 0;
        excess.assign(n + 1, 0);
        h.assign(n + 1, 0); h[s] = n;
        excess[s] = infty; excess[t] = -infty;
        Q.push((node){s, n});
        while (!Q.empty()) {
            int u = Q.top().u;
            Q.pop();
            Push(u, maxflow);
            Relabel(u);
        }
        return maxflow;
    }
};
