//树形DP
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector> 
#include<map>

using namespace std;

const int MAXN = 500;

struct EdgeType {
    int to, next;
};
map< string, int > M;
vector< EdgeType > edge;
int head[MAXN], d[MAXN][2], num;
bool f[MAXN][2];

inline int ID(const string& rhs) {
    if (!M.count(rhs)) M[rhs] = ++num;
    return M[rhs];
}
inline void AddEdge(int from, int to) {
    edge.push_back((EdgeType){to, head[from]});
    head[from] = edge.size() - 1;
}
void solve(int u) {
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        solve(v);
        
        int temp = d[v][0] > d[v][1] ? 0 : 1;
        d[u][0] += d[v][temp];
        if (d[v][0] == d[v][1]) f[u][0] = false;
        else if (!f[v][temp]) f[u][0] = false;
        
        d[u][1] += d[v][0];
        if (!f[v][0]) f[u][1] = false;
    }
}

int main() {
    int n;
    string employee, boss;
    while (cin >> n >> boss) {
        
        M.clear();
        num = 0;		
        memset(head, -1, sizeof head);
        memset(f, true, sizeof f);
        for (int i = 1; i <= n; i++) 
            d[i][1] = 1, d[i][0] = 0;
        edge.clear();
        
        ID(boss);
        for (int i = 1; i < n; i++) {
            cin >> employee >> boss;
            AddEdge(ID(boss), ID(employee)); 
        }
        
        solve(1);
        int temp = d[1][0] > d[1][1] ? 0 : 1;
        printf("%d ", d[1][temp]);
        if (f[1][temp] && d[1][0] != d[1][1]) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
