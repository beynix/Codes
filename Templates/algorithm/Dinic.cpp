struct Graph {
    static const int infty = 0x7f7f7f7f;
    struct edgetype {
        int to, next, flow, cap;
    };
    int n, m, s, t;
    std::vector< edgetype > edge;
    std::vector< bool > visit;
    std::vector< int > head, d, cur;
    std::queue< int > Q;
    Graph() {
        n = m = 0;
        head.clear(); d.clear(); edge.clear(); visit.clear(); cur.clear();
    }
    Graph(int n, int m) {
        this->n = n; this->m = m;
        head.resize(n + 1); d.resize(n + 1); visit.resize(n + 1); cur.resize(n + 1);
        head.assign(n + 1, -1);
    }
    void AddEdge(int from, int to, int cap) {
        edge.push_back((edgetype){to, head[from], 0, cap});
        head[from] = edge.size() - 1;
        edge.push_back((edgetype){from, head[to], 0, 0});
        head[to] = edge.size() - 1;
    }
    bool BFS() {
        visit.assign(n + 1, false);
        d.assign(n + 1, 0);
        while (!Q.empty()) Q.pop();
        Q.push(s); visit[s] = true;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int i = head[u]; i != -1; i = edge[i].next) {
                int v = edge[i].to;
                if (!visit[v] && edge[i].flow < edge[i].cap) {
                    visit[v] = true;
                    d[v] = d[u] + 1;
                    Q.push(v);
                }
            }
        }
        return visit[t];
    }
    long long DFS(int u, int alpha) {
        if (u == t || alpha == 0) return alpha;
        long long flow = 0, f;
        for (int& i = cur[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (d[u] + 1 == d[v] && (f = DFS(v, min(alpha, edge[i].cap - edge[i].flow))) > 0) {
                edge[i].flow += f; edge[i ^ 1].flow -= f; flow += f; alpha -= f;
                if (alpha == 0) break;
            }
        }
        return flow;
    }
    long long Maxflow(int s, int t) {
        this->s = s; this->t = t;
        long long maxflow = 0;
        while (BFS()) {
            cur.assign(head.begin(), head.end());
            maxflow += DFS(s, infty);
        }
        return maxflow;
    }
};
