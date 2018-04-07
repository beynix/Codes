struct BIT {
	int c[MAXN];
	inline int lowbit(int x) { return x & -x; }
	void add(int x, int d) {  
		for (int i = x; i <= MAXN; i += lowbit(i))
			c[i] += d;
	}
	int sum(int x) {  
    	int res = 0;  
    	for (int i = x; i > 0; i -= lowbit(i))
        	res += c[i];
		return res;  
	}  
};
