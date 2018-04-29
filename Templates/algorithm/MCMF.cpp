struct Graph {
    static const int infty = 0x7f7f7f7f;
    struct edgetype {
        int to, next, flow, cap, cost;
    };
    int n, m, s, t;
    std::vector< edgetype > edge;
    std::vector< bool > inQ;
    std::vector< int > head, dist, path;
    std::queue< int > Q;
    Graph() {
        n = m = 0;
        head.clear(); dist.clear(); edge.clear(); inQ.clear(); path.clear(); 
    }
    Graph(int n, int m) {
        this->n = n; this->m = m;
        head.resize(n + 1); dist.resize(n + 1); inQ.resize(n + 1); path.resize(n + 1); 
        head.assign(n + 1, -1);
    }
    void AddEdge(int from, int to, int cap, int cost) {
        edge.push_back((edgetype){to, head[from], 0, cap, cost});
        head[from] = edge.size() - 1;
        edge.push_back((edgetype){from, head[to], 0, 0, -cost});
        head[to] = edge.size() - 1;
    }
    bool FindPath() {
    	dist.assign(n + 1, infty);
    	inQ.assign(n + 1, false);
    	path.assign(n + 1, -1);
    	while (!Q.empty()) Q.pop();
    	Q.push(s); dist[s] = 0; inQ[s] = true; 
    	while (!Q.empty()) {
    		int u = Q.front(); Q.pop(); inQ[u] = false;
    		for (int i = head[u]; i != -1; i = edge[i].next) {
    			int v = edge[i].to;
    			if (edge[i].flow < edge[i].cap && dist[v] > dist[u] + edge[i].cost) {
    				dist[v] = dist[u] + edge[i].cost; path[v] = i; 
    				if (!inQ[v]) {
    					Q.push(v);
    					inQ[v] = true;
					}
				}
			}
		}
		return path[t] != -1;
	}
	void Argument(long long& Maxflow, long long& Mincost) {
		long long alpha = infty;
		for (int i = path[t]; i != -1; i = path[edge[i ^ 1].to]) 
			alpha = min(alpha, edge[i].cap - edge[i].flow);
		Maxflow += alpha; Mincost += dist[t] * alpha;
		for (int i = path[t]; i != -1; i = path[edge[i ^ 1].to]) {
			edge[i].flow += alpha;
			edge[i ^ 1].flow -= alpha;
		}
	}
    std::pair< long long, long long > MincostMaxflow(int s, int t) {
    	this->s = s; this->t = t;
    	long long Maxflow = 0, Mincost = 0;
    	while (FindPath())
    		Argument(Maxflow, Mincost);
    	return std::make_pair(Maxflow, Mincost);
	}
};
