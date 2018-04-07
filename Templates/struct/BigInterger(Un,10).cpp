struct BigInterger {
	static const int MAXNUM = 100000;
	static const int BASE = 10; 
	int num[MAXNUM], len; 
	BigInterger() {
		memset(num, 0, sizeof num);
		len = 0;
	}
	BigInterger operator = (long long temp) {
		len = 0;
		do {
			num[++len] = temp % 10;
			temp /= 10;			
		}while (temp == 0);
		return *this;
	}
	BigInterger operator = (const string &str) {
		len = str.size();
		for (int i = 0;i < str.size();i++)
			num[i + 1] = str[len - i - 1] - '0';
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
	BigInterger operator + (const BigInterger &rhs) {
		BigInterger ans;
		for (int i = 1, temp = 0;temp != 0 || i <= len || i <= rhs.len;i++) {
			temp += num[i] + rhs.num[i];
			ans.num[++ans.len] = temp % 10;
			temp /= 10;
		}
		return ans;
	}
	BigInterger operator - (const BigInterger &rhs) {
		BigInterger ans;
		ans.len = len;
		for (int i = 0;i <= len;i++) {
			if (num[i] < rhs.num[i])
				num[i + 1]--, num[i] += 10;
			ans.num[i] = num[i] - rhs.num[i];
		}
		ans.clear();
		return ans;
	}
	BigInterger operator * (const BigInterger &rhs) {
		BigInterger ans;
		ans.len = len + rhs.len;
		for (int i = 1;i <= len;i++) {
			int temp = 0;
			for (int j = 1;j <= rhs.len;j++) {
				ans.num[i + j - 1] += num[i] * rhs.num[j] + temp;
				temp = ans.num[i + j - 1] / 10;
				ans.num[i + j - 1] %= 10;
			}
			ans.num[i + rhs.len] = temp;
		}
		ans.clear();
		return ans;
	}
	BigInterger operator / (const int &rhs) {
		BigInterger ans;
		ans.len = len;
		for (int i = len, temp = 0;i >= 1;i--) {			
			temp = temp * 10 + num[i];
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
	for (int i = temp.len;i >= 1;i--)
		out << (char)(temp.num[i] + '0');
	return out;
}
