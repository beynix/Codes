struct part { int ex[MAXN]; bool vis[MAXN]; } X, Y;  
int n, match[MAXN], slack[MAXN], fit[MAXN][MAXN];  
bool DFS(int x) {  
    X.vis[x] = true;  
    for (int y = 1; y <= n; y++) {  
        if (Y.vis[y]) continue;  
        int gap = X.ex[x] + Y.ex[y] - fit[x][y];  
        if (gap == 0) {  
            Y.vis[y] = true;  
            if (match[y] == -1 || DFS(match[y])) {  
                match[y] = x;  
                return true;  
            }  
        }  
        else slack[y] = min(slack[y], gap);  
    }  
    return false;  
}  
int KM() {  
    memset(match, -1, sizeof match);  
    memset(Y.ex, 0, sizeof Y.ex);  
    for (int i = 1; i <= n; i++) {  
        X.ex[i] = fit[i][1];  
        for (int j = 2; j <= n; j++)   
            X.ex[i] = max(X.ex[i], fit[i][j]);  
    }  
    for (int i = 1; i <= n; i++) {  
        memset(slack, 127, sizeof slack);  
        while (true) {  
            memset(X.vis, false, sizeof X.vis);  
            memset(Y.vis, false, sizeof Y.vis);  
            if (DFS(i)) break;  
            int d = INT_MAX;  
            for (int j = 1;j <= n;j++)  
                if (!Y.vis[j])  
                    d = min(d, slack[j]);  
            for (int j = 1;j <= n;j++) {  
                if (X.vis[j]) X.ex[j] -= d;  
                if (Y.vis[j]) Y.ex[j] += d;  
                else slack[j] -= d;  
            }  
        }  
    }  
    int ans = 0;  
    for (int i = 1; i <= n; i++)  
        ans += fit[match[i]][i];  
    return ans;  
}  
