//莫队算法
#include <iostream>  
#include <cstdio>  
#include <string>  
#include <cstring>  
#include <fstream>  
#include <algorithm>  
#include <cmath>  
#include <queue>  
#include <stack>  
#include <vector>  
using namespace std;  
const int maxn = 200000 + 10;  
int n , m, a[maxn], pos[maxn], vis[maxn * 10];  
long long ans[maxn], num;  
struct node
{ 
	int l, r, id; 
	bool operator < (const node& rhs) const
	{
		return pos[l] != pos[rhs.l] ? l < rhs.l : r < rhs.r;
	}
}q[maxn];  
void add(long long x)  
{  
    vis[x]++;  
    num += x * (2 * vis[x] - 1);  
}  
void del(long long x)  
{  
    vis[x]--;  
    num -= x * (2 * vis[x] + 1);  
}  
int main()  
{  
    scanf("%d %d", &n, &m);
    double dis = sqrt(1.0 * n);  
    for(int i = 1 ;i <= n ;i++)  
    {  
        scanf("%d", &a[i]);  
        pos[i] = i / dis;  
    }  
    for(int i = 1 ;i <= m ;i++)  
    {  
        scanf("%d %d", &q[i].l, &q[i].r);  
        q[i].id = i;  
    }  
    sort(q + 1 ,q + m + 1);  
    num = 0;  
    int l = 1 , r = 0;  
    for(int i = 1 ; i <= m ; i ++)  
    {  
        while(r < q[i].r) add(a[++r]);  
        while(r > q[i].r) del(a[r--]);  
        while(l < q[i].l) del(a[l++]);  
        while(l > q[i].l) add(a[--l]);  
        ans[q[i].id] = num;  
    }  
    for(int i = 1 ; i <= m ; i ++)  
        printf("%I64d\n" , ans[i]);  
    return 0;  
}  
