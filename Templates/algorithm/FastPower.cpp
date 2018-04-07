typedef long long ll;
ll FastPower(ll a, ll p, ll k) {
	ll ans = 1;
	while (p) {
		if (p & 1)	ans = (ans * a) % k;
		a = (a * a) % k;
		p >>= 1;
	}
	return ans;
}
