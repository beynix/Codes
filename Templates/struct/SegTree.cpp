struct segtree {
	int l, r;
	segtree *lc, *rc;
	int sum, add;
	segtree(int l, int r, segtree *lc, segtree *rc)
		: l(l), r(r), lc(lc), rc(rc), sum(0), add(0) {}
	segtree(int l, int r, segtree *lc, segtree *rc, int sum, int add)
		: l(l), r(r), lc(lc), rc(rc), sum(sum), add(add) {}
	void cover(int rhs) {
		add += rhs;
		sum += rhs * (r - l + 1); 
	}
	void pushup() {
		sum = lc->sum + rc->sum; 
	}
	void pushdown() {
		if (add) {
			lc->cover(add);
			rc->cover(add);
			add = 0;
		}
	}
	void increase(int l, int r, int rhs) {
		if (l > this->r || r < this->l) return;
		else if (l <= this->l && this->r <= r) cover(rhs);
		else {
			pushdown();
			lc->increase(l, r, rhs);
			rc->increase(l, r, rhs);
			pushup();
		}
		return;
	}
	int query(int l, int r) {
		if (l > this->r || r < this->l) return 0;
		if (l <= this->l && this->r <= r) return sum;
		pushdown();
		return lc->query(l, r) + rc->query(l, r);
	}
	static segtree *build(int l, int r) {
		if (l > r) return NULL;
		else if (l == r) return new segtree(l, r, NULL, NULL);
		else {
			int mid = (l + r) >> 1;
			segtree *root = new segtree(l, r, build(l, mid), build(mid + 1, r));
			root->pushup();
			return root;
		}
	}
};
