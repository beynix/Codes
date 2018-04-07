struct Graph {  
	struct EdgeType { 
		int to, next, dist; 
	};  
    std :: queue< int > Q;   
    bool inQ[MAXV];
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
    	memset(inQ, false, sizeof inQ);
    	memset(dist, 63, sizeof dist);
    	Q.push(s);
    	dist[s] = 0;
    	inQ[s] = true;
    	while(!Q.empty()) {
	        int u = Q.front();
			Q.pop();
			inQ[u] = false;
        	for (int i = head[u]; i != -1; i = edge[i].next) {
            	int v = edge[i].to;
            	if(dist[v] > dist[u] + edge[i].dist) {
                	dist[v] = dist[u] + edge[i].dist;
                	if(!inQ[v])	{
                    	Q.push(v);
                    	inQ[v] = true;
                	}
            	}
        	}	
    	}
	}
    int Distance(int s, int t) {  
        SSSP(s);  
        return dist[t];  
    }  
}G;  
