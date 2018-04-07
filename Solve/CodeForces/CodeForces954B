#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
int main()
{
	int n, i, ans;
	string str;
	scanf("%d", &n);
	cin >> str;
	if (str.size() % 2 == 0) i = str.size() - 1, ans = 0;
	else i = str.size() - 2, ans = 1;
	bool flag = true;
	for (;i >= 0;i -= 2)
	{
		int len = (i >> 1) + 1;
		ans += 2;
		if (flag && str.substr(0, len) == str.substr((i >> 1) + 1, len))
		{
			ans += (i >> 1);
			break;
		}
	}
	cout << ans;
	return 0;
}
