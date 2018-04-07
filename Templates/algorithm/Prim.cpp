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
	int MST() {
		int ans = 0;
		memset(dist, 63, sizeof dist);
		while (!Q.empty()) Q.pop();
		Q.push((HeapNode){1, 0});
		dist[1] = 0;
		while (!Q.empty()) {
			int u = Q.top().point;
			Q.pop();
			ans += dist[u];
			dist[u] = 0;
			for (int i = head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].to;
				if (dist[v] > edge[i].dist) {
					dist[v] = edge[i].dist;
					Q.push((HeapNode){v, dist[v]});
				}
			}
		}
		return ans;
	}
}G;
