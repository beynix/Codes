inline int getint() {
    int num = 0, symbol = 1;
	char ch = getchar();
    while(ch < '0' || ch > '9') {
		if(ch == '-') symbol = -1;
		ch = getchar();
	}
    while(ch >= '0' && ch <= '9') {
		num = (num << 3) + (num << 1) + ch - '0';
		ch = getchar();
	}
    return num * symbol;
}
