//KMP + DP
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

const int MAXN = 100000 + 5;

char s[MAXN], t[MAXN];    
int next[MAXN], f[MAXN], cnt[MAXN];  

int main()  
{  
    scanf("%s %s", s, t);  
    
    int len_s = strlen(s), len_t = strlen(t);
    int i = 0, j = next[0] = -1;
    while (i < len_t) {
    	while (j != -1 && t[i] != t[j]) j = next[j];
    	next[++i] = ++j;
	}
	
    for (int i = len_t - 1; i < len_s; i++) {  
        bool flag = true;  
        for (int k = 0; k < len_t; k++) {  
            if (s[i - k] != t[len_t - 1 - k] && s[i - k] != '?') {  
                flag = false; 
				break;  
            }  
        }  
        f[i] = f[i - 1];  
        if (flag) {  
            cnt[i] = f[i - len_t];  
            for (int k = next[len_t]; k != -1; k = next[k]) 
                cnt[i] = std :: max(cnt[i], cnt[i - (len_t - k)]);  
            cnt[i]++;  
            f[i] = std :: max(f[i], cnt[i]);  
        }  
    }  
    printf("%d\n", f[len_s - 1]);  
}  
