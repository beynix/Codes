inline int randint(int l, int r) {
    const int number = 20000528;
    int x = rand();
    srand((time(NULL) << 16) | ((clock() << 16) >> 16) ^ x ^ number);
    return (rand() ^ x) % (r - l + 1) + l;
}
