//#include<cassert>
struct Fraction {
	int num, den;
	int gcd(int a, int b) {
		return b == 0 ? a : gcd(b, a % b);
	}
	Fraction() : num(0), den(1) {}
	Fraction(int num, int den) {
		if (den < 0) {
			num = -num;
			den = -den;
		}
		assert(den != 0);
		int tmp = gcd(abs(num), den);
		this->num = num / tmp;
		this->den = den / tmp;
	}
	Fraction operator + (const Fraction& rhs) const {
		return Fraction(num * rhs.den + den * rhs.num, den * rhs.den);
	}	
	Fraction operator - (const Fraction& rhs) const {
		return Fraction(num * rhs.den - den * rhs.num, den * rhs.den);
	}
	Fraction operator * (const Fraction& rhs) const {
		return Fraction(num * rhs.num, den * rhs.den);
	}
	Fraction operator / (const Fraction& rhs) const {
		return Fraction(num * rhs.den, den * rhs.num);
	}
	bool operator < (const Fraction& rhs) const {
		return num * rhs.den < den * rhs.num;
	}
	bool operator == (const Fraction& rhs) const {
		return num * rhs.den == den * rhs.num;
	}
};
