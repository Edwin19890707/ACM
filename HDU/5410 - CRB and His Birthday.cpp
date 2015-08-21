#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 2005

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

int n, m, a, b, w, mxa[N], dp[N];

int main() {
	int T;
	getInt(T);
	while (T--) {
		memset(mxa, 0, sizeof(mxa));
		memset(dp, 0, sizeof(dp));
		getInt(m); getInt(n);
		for (int i = 1; i <= n; i++) {
			getInt(w); getInt(a); getInt(b);
			mxa[w] = max(mxa[w], a);
			for (int j = 0; j + w <= m; j++) { //01���� dp[j]����m-j�����ı������ܻ�õ�����ֵ
				dp[j] = max(dp[j], dp[j + w] + a + b);
			}
		}
		for (int i = 1, mx = 0; i <= m; i++) { //��ȫ���� iΪ����
			if (mx < mxa[i]) { mx = mxa[i]; }
			else { continue; }
			for (int j = 0; j <= m; j++) { //����m-j�ı���
				for (int k = 1; k * i + j <= m; k++) { //����
					dp[j] = max(dp[j], dp[k * i + j] + mxa[i] * k);
				}
			}
		}
		printf("%d\n", dp[0]);
	}
}
