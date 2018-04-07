//差分 + 前缀和 
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int MAXN = 500000 + 10;
vector<int> words[MAXN];
int cnt[2 * MAXN], n, c;
void calc(int a, int b) {
    int index = 0;
    while (index < words[a].size() && index < words[b].size()) {
        if (words[a][index] != words[b][index]) break;
        index++;
    }
    if (index < words[a].size() && index < words[b].size()) {
        if (words[a][index] < words[b][index]) {
            cnt[0]++;
            cnt[c-words[b][index]+1]--;
            cnt[c+1-words[a][index]]++;
            cnt[c]--;
        }
        else {
            cnt[c+1-words[a][index]]++;
            cnt[c-words[b][index]+1]--;
        }
    }
    else if (index == words[a].size() && index != words[b].size()) {
        cnt[0]++;                                   
        cnt[c]--;                                  
    }
    else if (index != words[a].size() && index == words[b].size());
    else {
        cnt[0]++;
        cnt[c]--;
    }
}
int main() {
    scanf("%d%d", &n, &c); 
    for (int i = 1; i <= n; i++) {
        int len, w;
        scanf("%d", &len);
        while (len--) {
            scanf("%d", &w);
            words[i].push_back(w);
        }
    }
    for (int i = 1; i <= n - 1; i++) calc(i, i + 1);
    bool flag = false;
    int sum = 0;
    for (int i = 0; i < c; i++) {
        sum += cnt[i];
        if (sum == n - 1) {
            flag = true;
            printf("%d\n", i);
            return 0;
        }
    }
    if (!flag) printf("-1\n");
    return 0;
}
