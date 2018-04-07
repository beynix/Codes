#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<vector>

#define _x P[x]
#define x_ Q[x]
#define _y P[y]
#define y_ Q[y]

std::vector< int > P, Q; 
std::vector< std::pair< int, int > > result;

inline int randint(int l, int r) {
    const int number = 20000528;
    int x = rand();
    srand((time(NULL) << 16) | ((clock() << 16) >> 16) ^ x ^ number);
    return (rand() ^ x) % (r - l + 1) + l;
}

int main() {
	freopen("tree.in", "w", stdout);
	int n = 100000;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++) P.push_back(i);
	std::pair< int, int > temp; 
	int x = randint(0, P.size() - 1);
	temp.first = _x;
	Q.push_back(_x);
	P.erase(P.begin() + x);
	int y = randint(0, P.size() - 1);
	temp.second = _y;
	Q.push_back(_y);
	P.erase(P.begin() + y);
	result.push_back(temp);
	for (int i = 2; i < n; i++) {
		int x = randint(0, P.size() - 1);
		int y = randint(0, Q.size() - 1);
		int opt = randint(0, 1);
		if (opt) result.push_back(std::make_pair(_x, y_));
		else result.push_back(std::make_pair(y_, _x));
		Q.push_back(_x);
		P.erase(P.begin() + x);
	}
	for (int i = 1; i <= n; i++) {
		int x = randint(0, result.size() - 1);
		int y = randint(0, result.size() - 1);
		std::swap(result[x], result[y]);
	}
	for (unsigned int i = 0; i < result.size(); i++) 
		printf("%d %d\n", result[i].first, result[i].second);
	return 0;
} 
