struct BigInterger {
	static const int MAXNUM = 100000;
	static const int BASE = 1e8;
	static const int BIT = 8; 
	int num[MAXNUM], len; 
	BigInterger() {
		memset(num, 0, sizeof num);
		len = 0;
	}
	BigInterger operator = (long long temp)	{
		len = 0;
		do {
			num[++len] = temp % BASE;
			temp /= BASE;			
		}while (temp == 0);
		return *this;
	}
	BigInterger operator = (string &str) {
		len = 0;
		int i, j, temp;
		for (i = str.size() - 1;i >= BIT;i -= BIT) {
			temp = 0;
			for (j = BIT;j >= 1;j--)
				temp = temp * 10 + str[i - j + 1] - '0';
			num[++len] = temp;
		}
		temp = 0;
		for (j = 0;j <= i;j++)
			temp = temp * 10 + str[j] - '0';
		num[++len] = temp;
		return *this;
	}
	void clear() {
		while (num[len] == 0 && len > 1)
			len--;
	}
	bool operator < (const BigInterger &rhs) const {
		if (len != rhs.len) return len < rhs.len;
		for (int i = len;i >= 1;i--)
			if (num[i] != rhs.num[i])
				return num[i] < rhs.num[i];
		return false;
	}
	bool operator > (const BigInterger &rhs) const { return rhs < *this; }
	bool operator <= (const BigInterger &rhs) const { return !(rhs < *this); }
	bool operator >= (const BigInterger &rhs) const { return !(*this < rhs); }
	bool operator != (const BigInterger &rhs) const { return rhs < *this || *this < rhs; }
	bool operator == (const BigInterger &rhs) const { return !(rhs < *this) && !(*this < rhs); }
	BigInterger operator + (const BigInterger &rhs)	{
		BigInterger ans;
		for (int i = 1, temp = 0;temp != 0 || i <= len || i <= rhs.len;i++)	{
			temp += num[i] + rhs.num[i];
			ans.num[++ans.len] = temp % BASE;
			temp /= BASE;
		}
		return ans;
	}
	BigInterger operator - (const BigInterger &rhs) {
		BigInterger ans;
		ans.len = len;
		for (int i = 0;i <= len;i++) {
			if (num[i] < rhs.num[i])
				num[i + 1]--, num[i] += BASE;
			ans.num[i] = num[i] - rhs.num[i];
		}
		ans.clear();
		return ans;
	}
	BigInterger operator * (const BigInterger &rhs) {
		BigInterger ans;
		ans.len = len + rhs.len;
		for (int i = 1; i <= len; i++) {
			long long temp = 0;
			for (int j = 1; j <= rhs.len || temp != 0; j++) {
				temp += (long long)num[i] * rhs.num[j] + ans.num[i + j - 1];
				ans.num[i + j - 1] = temp % BASE;
				temp /= BASE;
			}
		}
		ans.clear();
		return ans;
	}
	BigInterger operator / (const int &rhs) {
		BigInterger ans;
		ans.len = len;
		long long temp = 0;
		for (int i = len; i >= 1; i--) {	
			temp = temp * BASE + num[i]; 
			ans.num[i] = temp / rhs;
			temp %= rhs;
		}
		ans.clear();
		return ans;
	}
};
istream& operator >> (istream &in, BigInterger &temp) {
	string str;
	in >> str;
	temp = str;
	return in;
}
ostream& operator << (ostream &out, const BigInterger &temp) {
	char buf[BigInterger :: BIT];
	sprintf(buf, "%d", temp.num[temp.len]);
	out << buf;
	for (int i = temp.len - 1; i >= 1; i--)
	{
		sprintf(buf, "%08d", temp.num[i]);
		out << buf; 
	}
	return out;
}
