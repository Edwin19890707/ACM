#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define N 100005
#define M 1000000007
#define judge(x,y) ((x)>=0&&(x)<h&&(y)>=0&&(y)<w)

template<class T> inline bool getInt(T &x) {
	char c = 0; T sign = 1;
	if ((c = getchar()) == EOF) { return false; }
	while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
	if (c == '-') { sign = -1; c = getchar(); }
	x = c - '0';
	while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
	x *= sign;
	return true;
}

int a[N];

int main() {
	int T, n, m;
	getInt(T);
	while (T--) {
		getInt(n);
		for (int i = 0; i < n; i++) {
			getInt(a[i]);
		}



	}
}
