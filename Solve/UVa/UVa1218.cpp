//树形DP
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

const int MAXN = 10000 + 10;
const int INF = 0x3f3f3f3f;

std::vector< int > G[MAXN];
int d[MAXN][3];

void solve(int u, int p) {
    for (unsigned int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == p) continue;
        solve(v, u);
        d[u][0] = std::min(d[u][0] + std::min(d[v][0], d[v][1]), INF);
        d[u][1] = std::min(d[u][1] + d[v][2], INF);		
    }
    d[u][2] = INF;
    for (unsigned int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == p) continue;
        d[u][2] = std::min(d[u][2], d[u][1] - d[v][2] + d[v][0]);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    while (true) {
        for (int i = 1; i <= n; i++) {
            G[i].clear();
            d[i][0] = 1; 
            d[i][1] = 0;
        }
            
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        
        solve(1, -1);
        
        printf("%d\n", std::min(d[1][0], d[1][2]));
        
        scanf("%d", &n);
        if (n == -1) break;
        scanf("%d", &n);
    }
    return 0;
}
