struct Graph { 
	struct _EdgeType { 
		int from, to, dist; 
		bool operator < (const _EdgeType& rhs) const {
			return dist < rhs.dist;
		}
	};  
    std :: vector< _EdgeType > _edge; 
    int f[MAXV];
    Graph() {  
        _edge.clear();  
    }  
    inline void _AddEdge(int from, int to, int dist) {  
        _edge.push_back((_EdgeType){from, to, dist});  
    }  
	inline int FindRoot(int x) {
		return f[x] == x ? x : f[x] = FindRoot(f[x]);
	}
    int MST(int n) {
		int num = 0, ans = 0;
		for (int i = 1; i <= n; i++) f[i] = i;
		sort(_edge.begin(), _edge.end());
		for (unsigned int i = 0; i < _edge.size(); i++) {
			int fu = FindRoot(_edge[i].from);
			int fv = FindRoot(_edge[i].to);
			if (fu != fv)
			{
				f[fu] = fv;
				ans += _edge[i].dist;
				if (++num == n - 1)
					break;
			}
		}
		return ans;
	}
};  
