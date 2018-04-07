vector<int> G[Vmax];
stack<int> S;
int tmpdfn, scc_cnt, dfn[Vmax], low[Vmax], scc[Vmax]; 
void Tarjan(int u) {
    dfn[u] = low[u] = ++tmpdfn;
    S.push(u);
    int v = 0;
    for (int i = 0; i < G[u].size(); i++) {
        v = G[u][i];
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!scc[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        scc_cnt++;
        do {
            v = S.top();
            S.pop();
            scc[v] = scc_cnt;
        }while (u != v);
    }
}
void Get_SCC(int n) {
    tmpdfn = scc_cnt = 0;
    memset(scc, 0, sizeof scc);
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low); 
    while (!S.empty()) S.pop();
    for (int i = 1;i <= n;i++)
        if (!dfn[i])
            Tarjan(i);
}
