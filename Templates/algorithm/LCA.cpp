int anc[1005][25], fa[1005], deep[1005];
std :: vector<int> tree[1005];
void dfs(int x)
{
    anc[x][0] = fa[x];
    for (int i = 1; i <= 25; i++)
        anc[x][i] = anc[ anc[x][i - 1] ][i - 1];
    for (int i = 0; i < tree[x].size(); i++)
        if (tree[x][i] != fa[x])
        {
            int y = tree[x][i];
            fa[y] = x;
            deep[y] = deep[x] + 1;
            dfs(y);
        }
}
void swim(int& x, int H, int& ans) {
	for (int i = 0; H > 0; i++) {
		if (H & 1) 
			x = anc[x][i];
		H >>= 1;
	}
}
int LCA(int x, int y) {
    if (deep[x] < deep[y]) swap(x, y);
    swim(x, deep[x] - deep[y], ans);
    if (x == y) return x;
    for (int i = 25; i >= 0; i--)
        if (anc[x][i] != anc[y][i]) {
            x=anc[x][i];
            y=anc[y][i];
        } 
    return anc[x][0];
}

