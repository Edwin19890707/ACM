//������
ll powMod(ll a, ll b, ll m = M) {
	ll r = 1; a %= m;
	while (b) {
		if (b & 1) { r = r * a % m; }
		a = a * a % m;
		b >>= 1;
	}
	return r;
}
//ģ������˷�
ll mulMod(ll a, ll b, ll m = M) {
	ll r = 0; a %= m; b %= m;
	while (b) {
		if (b & 1) { r = (r + a) % m; }
		a = (a << 1) % m;
		b >>= 1;
	}
	return r;
}
//������ + ģ������˷�
ll powMod(ll a, ll b, ll m = M) {
	ll r = 1; a %= m;
	while (b) {
		if (b & 1) { r = mulMod(r, a, m); }
		a = mulMod(a, a, m);
		b >>= 1;
	}
	return r;
}

//------------------------------------------------------------------------------

//����ɸ
bool isprime[N];
void getPrime() {
	memset(isprime, -1, sizeof(isprime));
	isprime[0] = isprime[1] = false;
	for (ll i = 2; i < N; i++) {
		if (isprime[i]) { for (ll j = i * i; j < N; j += i) { isprime[j] = false; } }
	}
}

int prime[N + 1];
void getPrime() {
	for (int i = 2; i <= N; i++) {
		if (!prime[i]) { prime[++prime[0]] = i; }
		for (int j = 1; j <= prime[0] && prime[j] <= N / i; j++) {
			prime[prime[j] * i] = 1;
			if (i % prime[j] == 0) { break; }
		}
	}
}

//------------------------------------------------------------------------------

//�����ֽ�
ll factor[100][2];
int getFactors(ll x, ll factor[][2] = factor) {
	int fatCnt = 0;
	for (int i = 1; prime[i] <= x / prime[i]; i++) {
		factor[fatCnt][1] = 0;
		if (x % prime[i] == 0) {
			factor[fatCnt][0] = prime[i];
			while (x % prime[i] == 0) {
				factor[fatCnt][1]++;
				x /= prime[i];
			}
			fatCnt++;
		}
	}
	if (x != 1) {
		factor[fatCnt][0] = x;
		factor[fatCnt++][1] = 1;
	}
	return fatCnt;
}

//Miller Rabin��������
const int S = 10;
//����ret = (a * b) % m
ll mulMod(ll a, ll b, ll m = M) {
	ll r = 0; a %= m; b %= m;
	while (b) {
		if (b & 1) { r = (r + a) % m; }
		a = (a << 1) % m;
		b >>= 1;
	}
	return r;
}
//����ret = (a^n) % m
ll powMod(ll a, ll b, ll m = M) {
	ll r = 1; a %= m;
	while (b) {
		if (b & 1) { r = mulMod(r, a, m); }
		a = mulMod(a, a, m);
		b >>= 1;
	}
	return r;
}
//ͨ��a^(n - 1) = 1(mod n)���ж�n�ǲ�������
//n - 1 = x * 2^t �м�ʹ�ö����ж�
bool check(ll a, ll n, ll x, ll t) {
	ll ret = powMod(a, x, n), last = ret;
	for (int i = 1; i <= t; i++) {
		ret = mulMod(ret, ret, n);
		if (ret == 1 && last != 1 && last != n - 1) { return true; }
		last = ret;
	}
	if (ret != 1) { return true; }
	else { return false; }
}

bool Miller_Rabin(ll n) {
	if (n < 2) { return false; }
	if (n == 2) { return true; }
	if ((n & 1) == 0) { return false; }
	ll x = n - 1, t = 0;
	while ((x & 1) == 0) {x >>= 1; t++;}
	srand(time(NULL));
	for (int i = 0; i < S; i++) {
		ll a = rand() % (n - 1) + 1;
		if (check(a, n, x, t)) { return false; }
	}
	return true;
}

//pollard rho�����طֽ�
ll factor[100]; //�����طֽ���(����ʱ����)
int tol; //�����صĸ���

ll gcd(ll a, ll b) {
	while (b != 0) {
		ll t = a % b;
		a = b;
		b = t;
	}
	return a >= 0 ? a : -a;
}
//�ҳ�һ������
ll pollard_rho(ll x, ll c) {
	srand(time(NULL));
	ll i = 1, k = 2, x0 = rand() % (x - 1) + 1, y = x0;
	while (true) {
		i++;
		x0 = (mulMod(x0, x0, x) + c) % x;
		ll d = gcd(y - x0, x);
		if (d != 1 && d != x) { return d; }
		if (y == x0) { return x; }
		if (i == k) {y = x0; k += k;}
	}
}
//��n���������ӷֽ�,����factor,k����Ϊ107���Ҽ���
void findfac(ll n, int k = 107) {
	if (n == 1) { return; }
	if (Miller_Rabin(n)) { factor[tol++] = n; return; }
	ll p = n;
	int c = k;
	while (p >= n) { p = pollard_rho(p, c--); } //ֵ�仯����ֹ��ѭ��k
	findfac(p, k);
	findfac(n / p, k);
}

//------------------------------------------------------------------------------

//ŷ������
int getFacEul(ll n, ll factor[][2] = factor) {
	int fatCnt = getFactors(n);
	for (int i = 0; i < fatCnt; i++) {
		n = n / factor[i][0] * (factor[i][0] - 1);
	}
}

ll eular(ll n) {
	ll ans = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ans -= ans / i;
			while (n % i == 0) { n /= i; }
		}
	}
	if (n > 1) { ans -= ans / n; }
	return ans;
}

int euler[N];
void getEuler() {
	euler[1] = 1;
	for (int i = 2; i < N; i++) {
		if (!euler[i]) {
			for (int j = i; j < N; j += i) {
				if (euler[j] == 0) { euler[j] = j; }
				euler[j] = euler[j] / i * (i - 1);
			}
		}
	}
}

//------------------------------------------------------------------------------

//����Ԫ(ax = 1(mod m)��xֵ)
//��չŷ�����(��ax + by = gcd(a, b)�Ľ�),�����xΪa��b��ģ��Ԫ
ll extendGcd(ll a, ll b, ll &x, ll &y) {
	if (a == 0 && b == 0) { return -1; } //�����Լ��
	if (b == 0) { x = 1; y = 0; return a; }
	ll d = extendGcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
ll modReverse(ll a, ll m) {
	ll x, y;
	ll d = extendGcd(a, m, x, y);
	if (d == 1) { return (x % m + m) % m; }
	else { return -1; }
}

//ֻ����0 < a < m�����,a��m����
ll inv(ll a, ll m = M) {
	if (a == 1) { return 1; }
	return inv(m % a, m) * (m - m / a) % m;
}

//����С����,mΪ����,a��m����
ll inv(ll a, ll m = M) {
	return powMod(a, m - 2, m);
}

//------------------------------------------------------------------------------

//�����
ll com(ll n, ll m) {
	if (n - m > m) { m = n - m; }
	ll s = 1;
	for (ll i = 0, j = 1; i < m; i++) {
		s *= n - i;
		for (; j <= m && s % j == 0; j++) { s /= j; }
	}
	return s;
}

//�����ȡģ
//Ԥ����׳�
ll fac[N];
void getFac(ll p) {
	fac[0] = 1;
	for (ll i = 1; i <= p; i++) { fac[i] = (fac[i - 1] * i) % p; }
}
//Lucas���� p <= 10^5
ll lucas(ll n, ll m, ll p) {
	if (m > n - m) { m = n - m; }
	ll res = 1;
	while (n && m) {
		ll a = n % p, b = m % p;
		if (a < b) { return 0; }
		res = res * fac[a] * powMod(fac[b] * fac[a - b] % p, p - 2, p) % p;
		n /= p; m /= p;
	}
	return res;
}
//�й�ʣ�ඨ��
ll CRT(ll a[], ll m[], int k) {
	ll mm = 1, ans = 0;
	for (int i = 0; i < k; i++) { mm *= m[i]; }
	for (int i = 0; i < k; i++) {
		ll x, y, t = mm / m[i];
		ans = (ans + t * inv(t, m[i]) * a[i]) % mm;
	}
	if (ans < 0) { ans += mm; }
	return ans;
}

//------------------------------------------------------------------------------

//ģ���Է�����
int m[10], a[10]; //ģ��Ϊm,����Ϊa, X % m = a
bool solve(int &m0, int &a0, int m, int a) {
	ll y, x;
	int g = extendGcd(m0, m, x, y);
	if (abs(a - a0) % g) { return false; }
	x *= (a - a0) / g;
	x %= m / g;
	a0 = (x * m0 + a0);
	m0 *= m / g;
	a0 %= m0;
	if (a0 < 0) { a0 += m0; }
	return true;
}
//�޽ⷵ��false,�нⷵ��true;
//�����ʽ���Ϊ a0 + m0 * t (0 <= a0 < m0)
bool MLES(int &m0 , int &a0, int n) { //��ΪX = a0 + m0 * k
	bool flag = true;
	m0 = 1; a0 = 0;
	for (int i = 0; i < n; i++) {
		if (!solve(m0, a0, m[i], a[i])) { flag = false; break; }
	}
	return flag;
}
