int n, c[MAXN], number[MAXN];   
struct Node { int val, num; } a[MAXN];  
bool cmp(Node a, Node b) { return a.val > b.val; }  
int lowbit(int x) { return x & (-x); }  
void add(int x) {
	for (int i = x; i <= n; i += lowbit(i)) c[i]++;
}
int query(int x) {
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i)) ans += c[i];
	return ans;	
}
int reverse_order_pair() {
	int ans = 0, temp = -1, tot = 0;
	stable_sort(a + 1, a + n + 1, cmp);  
    for (int i = 1; i <= n; i++) {  
        if (a[i].val != temp) {  
            tot++;  
            temp = a[i].val;  
        }  
        number[a[i].num] = tot;  
    }  
    for (int i = 1; i <= n; i++) {  
        add(number[i]);  
        ans += query(number[i] - 1);  
    }  
    return ans;
}
