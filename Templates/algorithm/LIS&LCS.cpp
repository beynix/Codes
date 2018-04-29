int LIS(std::vector< int > &a) {
	int ans = 1; 
	std::vector< int > f(a.size(), 1);
	for (unsigned int i = 2; i <= a.size() - 1; i++) 
		for (unsigned int j = i - 1; j >= 1; j--) 
			if (a[i] > a[j] && f[i] < f[j] + 1) {
				f[i] = f[j] + 1;
				if (f[i] > ans)
					ans = f[i];
			}
	return ans;
}

int LIS(std::vector< int > &a) {
	std::vector< int > f;
	f.push_back(a[1]);
	for (unsigned int i = 2; i < a.size(); i++)
		if (a[i] < f.back()) 
			f[std::upper_bound(f.begin(), f.end(), a[i]) - f.begin()] = a[i]; 
		else f.push_back(a[i]);	
	return f.size();
}


int LCS(int n, std::vector< int > &a, int m, std::vector< int > &b) {
	std::vector< std::vector< int > > f(n + 1, std::vector< int >(m + 1));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (a[i] == b[j]) f[i][j] = f[i - 1][j - 1] + 1;
			else f[i][j] = std::max(f[i - 1][j], f[i][j - 1]);
	return f[n][m];
}

int LCS(std::vector< int > &a, std::vector< int > &b) {
	static const int MAXN = 1000000 + 10;
	std::vector< int > c(1), index(MAXN);
	for (unsigned int i = 1; i < b.size(); i++) index[b[i]] = i;
	for (unsigned int i = 1; i < a.size(); i++) 
		if (index[a[i]]) c.push_back(index[a[i]]);
	return LIS(c);						
}
