//树形DP
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

const int MAXN = 200000 + 10;

struct EdgeType {
	int to, type; 
};
std::vector< EdgeType > G[MAXN];
int f[MAXN],dir[MAXN];

void dfs(int u, int p) {
    f[u] = 0;
    for (unsigned int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].to;
        if (v == p) continue;
        dir[v] = G[u][i].type;
        dfs (v, u);
        f[u] += f[v] + dir[v];
    }
}

void solve(int u, int p) {
    for (unsigned int i = 0; i < G[u].size(); i++) {
        int v = G[u][i].to;
        if (v == p) continue;
        f[v] = f[u] + (dir[v] ? -1 : 1);
        solve(v, u);
    }
}

int main () {
	int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
    	int u, v;
        scanf ("%d%d" , &u , &v);
        G[u].push_back((EdgeType){v, 0});
        G[v].push_back((EdgeType){u, 1});
    }
    dfs(1, -1);
    solve(1, -1);
    int ans = 0x3f3f3f3f;
    std::vector< int > result;
    for (int i = 1; i <= n; i++) {
    	if (f[i] < ans) {
    		ans = f[i];
    		result.clear();
		}
		if (f[i] == ans)
            result.push_back(i);
    }
    printf("%d\n", ans);
    for (unsigned int i = 0 ; i < result.size(); i++ )
        printf ("%d " ,result[i]);
}
