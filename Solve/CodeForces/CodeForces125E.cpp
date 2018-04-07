//单独限制最小生成树
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>

const int MAXN=5010;
const int MAXM=100010;
const int INF = 0x3f3f3f3f;

struct edge{
	int u, v;
	double w;
}e[MAXM];
std :: vector< int > result;
int n, m, k, p, ans = INF, cap, parts;
int order[MAXM], f[MAXN];
double weight;
inline int getfather(int x) {
	return f[x] == x ? x : f[x] = getfather(f[x]);
}
bool compare(const int& l, const int& r) {
	double p = e[l].w, q = e[r].w;
	if(e[l].u == 1)	p += weight;
	if(e[r].u == 1) q += weight;
	return p < q;
}
void Kruskal(bool special) {
	for (int i = 1; i <= n; i++) f[i] = i;
	result.clear(); cap = 0; parts = n;
	std::sort(order + 1, order + m + 1, compare);
	for(int i = 1; i <= m; i++) {
		int t = order[i];
		int fu = getfather(e[t].u);
		int fv = getfather(e[t].v);
		if (fu == fv) continue;
		if(e[t].u == 1) cap++;
		if (special && cap > k) {
			cap--;
			continue;
		}
		f[fu] = fv;
		result.push_back(order[i]);
		if(--parts == 1)
			return;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%lf", &e[i].u, &e[i].v, &e[i].w);
		if (e[i].u > e[i].v) std :: swap(e[i].u, e[i].v);
		if (e[i].u == 1) p++;
	}
	if (p < k || (n > 1 && !k)) {
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= m; i++) order[i] = i;
	Kruskal(false);
    if (parts > 1) {
        puts("-1");
        return 0;
    }
	double l = -1e5, r = 1e5 + 0.5;
    while (true) {
        if(cap == k)
			break;
        if(l + 0.1 > r && cap > k)
			break;
        double mid = (l + r) / 2.0;
        weight = mid;
		Kruskal(false);
        if(cap < k) r = mid;
        else l = mid;
    }
    if(cap != k) Kruskal(true);
    printf("%d\n", result.size());
    sort(result.begin(), result.end());
    for(int i = 0; i < result.size(); i++)
    	printf("%d ", result[i]);
	return 0;
} 
