struct EdgeType {
	int to, next, dist;
};

std::vector< EdgeType > edge;
int label;
int father[MAXN], deep[MAXN], weight[MAXN], value[MAXN];
int son[MAXN], pos[MAXN], top[MAXN], head[MAXN];
bool visit[MAXN];

inline void AddEdge(int from, int to, int dist) {
	edge.push_back((EdgeType){to, head[from], dist});
	head[from] = edge.size() - 1;
}

inline int getint() {
    int num = 0, symbol = 1;
	char ch = getchar();
    while(ch < '0' || ch > '9') {
		if(ch == '-') symbol = -1;
		ch = getchar();
	}
    while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + ch - '0';
		ch = getchar();
	}
    return num * symbol;
}

struct segtree {
	int l, r;
	segtree *lc, *rc;
	long long sum, add;
	segtree(int l, int r, segtree *lc, segtree *rc) :
		l(l), r(r), lc(lc), rc(rc), sum(0), add(0) {}
	void cover(long long rhs) {
		add += rhs;
		sum += rhs * (r - l + 1); 
	}
	void pushup() {
		sum = lc->sum + rc->sum;
	}
	void pushdown() {
		if (add) {
			lc->cover(add);
			rc->cover(add);
			add = 0;
		}
	}
	void increase(int l, int r, long long rhs) {
		if (l > this->r || r < this->l) return;
		if (l <= this->l && this->r <= r) cover(rhs);
		else {
			pushdown();
			lc->increase(l, r, rhs);
			rc->increase(l, r, rhs);
			pushup();
		}
		return;
	}
	long long query(int l, int r) {
		if (l > this->r || r < this->l) return 0;
		if (l <= this->l && this->r <= r) return sum;
		pushdown();
		return lc->query(l, r) + rc->query(l, r);
	}
	static segtree* build(int l, int r) {
		if (l == r) return new segtree(l, r, NULL, NULL);
		int mid = (l + r) >> 1;
		return new segtree(l, r, build(l, mid), build(mid + 1, r));
	}
	
}*root;

void dfs_1(int x, int f, int d) {
	father[x] = f;
	deep[x] = d;
	weight[x] = 1;
	son[x] = 0;
	int maxsize = 0;
	visit[x] = true;
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int child = edge[i].to;
		if (child == f || visit[child]) continue;
		value[child] = edge[i].dist;
		dfs_1(child, x, d + 1);
		weight[x] += weight[child];
		if (weight[child] > maxsize) {
			maxsize = weight[child];
			son[x] = child;
		}
	}
}
void dfs_2(int x, int anc) {
	pos[x] = ++label;
	top[x] = anc;
	visit[x] = true;
	if (son[x]) dfs_2(son[x], anc);
	for (int i = head[x]; i != -1; i = edge[i].next) {
		int child = edge[i].to;
		if (child == father[x] || child == son[x] || visit[child]) continue;
		dfs_2(child, child);
	}
}
void updata(int x, int y, int z) {
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
		root->increase(pos[top[x]], pos[x], z);
		x = father[top[x]];
	}
	if (deep[x] > deep[y]) std::swap(x, y);
	root->increase(pos[x], pos[y], z);
}
long long query(int x, int y) {
	long long ans = 0;	
	while (top[x] != top[y]) {
		if (deep[top[x]] < deep[top[y]]) std::swap(x, y);
		ans = (ans + root->query(pos[top[x]], pos[x]));
		x = father[top[x]];
	}
	if (deep[x] > deep[y]) std::swap(x, y);
	return ans + root->query(pos[x], pos[y]);
}
