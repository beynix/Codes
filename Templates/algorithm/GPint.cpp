inline int getint() {
	int num = 0, symbol = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		ch == '-' ? symbol = -1 : 0;
		ch = getchar();
	}
    while (ch >= '0' && ch <= '9') 
        num = (num << 3) + (num << 1) + (ch ^ '0'),
        ch = getchar();
    return num * symbol;
}
inline void putint(int num) {
	if (num > 9) putint(num / 10);
	putchar(num % 10 + '0');
}
