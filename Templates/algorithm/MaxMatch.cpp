bool f[MAXN][MAXN], visit[MAXN];  
struct part {  
    int num, match[MAXN];  
}X, Y;  
int DFS(int u) {  
    for (int v = 1; v <= Y.num; v++)  
	    if (f[u][v] && !visit[v]) {  
            visit[v] = true;  
            if (Y.match[v] == -1 || DFS(Y.match[v])) {  
                X.match[u] = v;  
                Y.match[v] = u;  
                return 1;  
            }  
        }  
    return 0;  
}  
int MaxMatch() {  
    int ans = 0;  
    memset(X.match, -1, sizeof X.match);  
    memset(Y.match, -1, sizeof Y.match);  
    for (int i = 1; i <= X.num; i++)  
        if (X.match[i] == -1) {  
            memset(visit, false, sizeof visit);  
            ans += DFS(i);  
        }  
    return ans;  
}  
