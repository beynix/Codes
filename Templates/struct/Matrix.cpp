typedef long long ll;
struct Matrix {  
 	int row, col, limit;
	std::vector< std::vector< ll > > num;
  	Matrix() {
  		row = col = 0;
  		limit = 0x3f3f3f3f;
  		num.clear();
	}
	Matrix(int _row, int _col, int _limit) {
		this->row = _row;
		this->col = _col;
		this->limit = _limit;
		num.clear();
		num.resize(row + 1);
		for (int i = 1; i <= row; i++)
			num[i].resize(col + 1);
	}
	Matrix(int _row, int _col, int _limit, long long *list) {
		this->row = _row;
		this->col = _col;
		this->limit = _limit;
		num.clear();
		num.resize(row + 1);
		for (int i = 1; i <= _row; i++) {
			num[i].resize(col + 1);
			for (int j = 1; j <= _col; j++) 
				num[i][j] = list[(i - 1) * _row + j];
		}
	}
    Matrix operator + (const Matrix& rhs) {
    	assert(this->row == rhs.row && this->col == rhs.col);
    	for (int i = 1; i <= row; i++)
    		for (int j = 1; j <= col; j++) 
    			this->num[i][j] += rhs.num[i][j],
    			this->num[i][j] %= limit;
    	return *this;
	}
	Matrix operator - (const Matrix& rhs) {
    	assert(this->row == rhs.row && this->col == rhs.col);
    	for (int i = 1; i <= row; i++)
    		for (int j = 1; j <= col; j++) 
    			this->num[i][j] -= rhs.num[i][j],
    			this->num[i][j] %= limit;
    	return *this;
	}
	Matrix operator * (const long long& rhs) {
		for (int i = 1; i <= this->row; i++) 
			for (int j = 1; j <= this->col; j++)
				this->num[i][j] *= rhs,
				this->num[i][j] %= this->limit;
	}
	Matrix operator * (const Matrix& rhs) {
		assert(this->col == rhs.row);
		Matrix ans = Matrix(this->row, col, this->limit);
		for (int i = 1; i <= this->row; i++) 
			for (int j = 1; j <= rhs.col; j++)
				for (int k = 1; k <= this->col; k++) 
					ans.num[i][j] += this->num[i][k] * rhs.num[k][j],
					ans.num[i][j] %= this->limit;
		return ans;
	}
	Matrix operator ^ (ll p) {
		assert(this->row == this->col);
		Matrix ans = Matrix(this->row, this->col, this->limit);
		for (int i = 1; i <= this->row; i++) 
			ans.num[i][i] = 1;
		while (p) {
			if (p & 1) ans = ans * *this;
			*this = *this * *this;
			p >>= 1;
		}
		return ans;
	}
};  
