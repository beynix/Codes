struct Graph {
	struct EdgeType {
		int to, next, dist;
	};
	struct HeapNode {
    	int point, dist;
    	bool operator < (const HeapNode& rhs) const {
        	return dist > rhs.dist;
    	}
	};
	std :: priority_queue< HeapNode > Q; 
	bool done[MAXV];
	int dist[MAXV], head[MAXV];
	std :: vector< EdgeType > edge;
	Graph() {
		edge.clear();
		memset(head, -1, sizeof head);
	}
	inline void AddEdge(int from, int to, int dist) {
		edge.push_back((EdgeType){to, head[from], dist});		
		head[from] = edge.size() - 1;
	}
	void SSSP(int s) {
		memset(dist, 63, sizeof dist);
		memset(done, false, sizeof done);
		while (!Q.empty()) Q.pop();
		Q.push((HeapNode){s, 0});
		dist[s] = 0;
		while (!Q.empty()) {
			int u = Q.top().point;
			Q.pop();
			if (done[u]) continue;
			done[u] = true;
			for (int i = head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].to;
				if (dist[v] > dist[u] + edge[i].dist) {
					dist[v] = dist[u] + edge[i].dist;
					Q.push((HeapNode){v, dist[v]});
				}
			}
		}
	}
	int Distance(int s, int t) {
		SSSP(s);
		return dist[t];
	}
}G;
