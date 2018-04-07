#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<string>
using namespace std;
int main()
{
	int n, ans;
	char ch;
	string str;
	scanf("%d%c", &n, &ch);
	ans = n;
	cin >> str;
	for (int i = 0;i < str.size() - 1;i++)
	{
		if ((str[i] == 'R' && str[i + 1] == 'U') || (str[i] == 'U' && str[i + 1] == 'R'))
		{
			ans--;
			i++;
		}
	}
	int len = str.size() - 1;
	printf("%d", ans);
	return 0;
}
