namespace Istream {
	static const int BUF = 50000000;
	inline char get() {
    	static char buf[BUF], *h, *t;
    	h == t ? t = (h = buf) + fread(buf, 1, BUF, stdin) : 0;
    	return h == t ? -1 : *h++;
	}
	inline int getint() {
		int num = 0, symbol = 1;
		char ch = get();
		while (!isdigit(ch)) {
			if (ch == -1) return 0;
			ch == '-' ? symbol = -1 : 0;
			ch = get();
		}
    	while (isdigit(ch)) 
        	num = (num << 3) + (num << 1) + (ch ^ '0'),
        	ch = get();
    	return num * symbol;
	}
}
namespace Ostream {
	static const int BUF = 50000000;
	char buf[BUF], *h = buf;
	inline void put(char ch) {
    	h == buf + BUF ? (fwrite(buf, 1, BUF, stdout), h = buf) : 0;
    	*h++ = ch;
	}
	inline void putint(int num) {
    	static char _buf[30];
    	sprintf(buf, "%d", num);
    	for (char *s = _buf; *s; s++) put(*s);
    	put('\n');
	}
	inline void finish() {
    	fwrite(buf, 1, h - buf, stdout);
	}
}
