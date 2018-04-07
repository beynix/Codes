//树形DP
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

const int MAXN = 100000 + 10;
const int INF = 0x3f3f3f3f;

struct EdgeType {
    int to, next;
};
std::vector< EdgeType > edge;
int head[MAXN], d[MAXN][4];

inline int _min(int a, int b, int c) {
    return std::min(a, std::min(b, c));
}
inline void AddEdge(int u, int v) {
    edge.push_back((EdgeType){v, head[u]});
    head[u] = edge.size() - 1;
}
void solve(int u, int p) {
    int sum = 0, min = INF;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (v == p) continue;;
        solve(v, u); 
        d[u][0] += std::min(d[v][1], d[v][2]);
        d[u][1] += _min(d[v][0], d[v][1], d[v][2]);
        d[u][2] += std::min(_min(d[v][0], d[v][1], d[v][2]), d[v][3]);
        d[u][3] += _min(d[v][0], d[v][1], d[v][2]);
        int temp = _min(d[v][0], d[v][1], d[v][2]);
        sum += temp;
        min = std::min(min, d[v][2] - temp);
    }
    d[u][1] = std::min(d[u][1], sum + min);
}

int main() {
    int n, p, q;
    while (scanf("%d%d%d", &n, &p, &q) != EOF && n != 0) {
        memset(head, -1, sizeof head);
        edge.clear();
        for (int i = 1; i <= n; i++) {
            d[i][0] = 0;
            d[i][1] = p;
            d[i][2] = q;
            d[i][3] = 0;
        }
        
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
            AddEdge(v, u);
        }
        
        solve(1, -1);
        
        printf("%d\n", _min(d[1][0], d[1][1], d[1][2]));
    }
    return 0;
} 
