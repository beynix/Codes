#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
const int MAXV = 1000 + 5;
bool f[MAXV][MAXV];
struct edge { int to, next, dist; };  
struct Graph 
{  
    vector<edge> E;  
    queue<int> Q;  
    int dist[MAXV][MAXV], head[MAXV];
    bool inQ[MAXV];
    Graph()  
    {  
        E.clear();  
        memset(head, -1, sizeof head);
    	memset(dist, 63, sizeof dist);
    }  
    inline void AddEdge(int from, int to)  
    {  
        E.push_back((edge){to, head[from]});  
        head[from] = E.size() - 1;  
    }  
    void SSSP(int s)
	{
    	memset(inQ, false, sizeof inQ);
    	Q.push(s);
    	dist[s][s] = 0;
    	inQ[s] = true;
    	while(!Q.empty())
		{
	        int u = Q.front();
			Q.pop();
			inQ[u] = false;
        	for (int i = head[u];i != -1;i = E[i].next)
        	{
            	int v = E[i].to;
            	if(dist[s][v] > dist[s][u] + 1)
            	{
                	dist[s][v] = dist[s][u] + 1;
                	if(!inQ[v])
                	{
                    	Q.push(v);
                    	inQ[v] = true;
                	}
            	}
        	}	
    	}
	}
    int Distance(int s, int t)  
    {  
        SSSP(s);  
        return dist[s][t];  
    }  
};  

Graph G;  
int main()
{
	int n, m, s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for (int i = 1;i <= m;i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		f[u][v] = f[v][u] = true;
		G.AddEdge(u, v);
		G.AddEdge(v, u);
	}
	G.SSSP(s);
	G.SSSP(t);
	int ans = 0;
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++)
			if (i != j && !f[i][j] 
			&& G.dist[s][i] + G.dist[t][j] + 1 >= G.dist[s][t] 
			&& G.dist[s][j] + G.dist[t][i] + 1 >= G.dist[s][t])  
				ans++;
	cout << ans / 2 << endl;
	return 0;
}
