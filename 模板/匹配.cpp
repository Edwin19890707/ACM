//����ͼ���Ȩƥ��

//KM + �ڽӾ��� O(nx*nx*ny)
//������СȨƥ�䣬�ɽ�Ȩֵȡ�෴�������ȡ�෴��
//��ı�Ŵ�0��ʼ
#define N 305
#define INF 0x3f3f3f3f
int nx, ny, g[N][N]; //���� ����ͼ����
int linker[N], lx[N], ly[N]; //y�и���ƥ��״̬��x,y�еĵ���
int slack[N];
bool visx[N], visy[N];
bool DFS(int x) {
	visx[x] = true;
	for (int y = 0; y < ny; y++) {
		if (visy[y]) { continue; }
		int tmp = lx[x] + ly[y] - g[x][y];
		if (tmp == 0) {
			visy[y] = true;
			if (linker[y] == -1 || DFS(linker[y])) {
				linker[y] = x; return true;
			}
		} else if (slack[y] > tmp) {
			slack[y] = tmp;
		}
	}
	return false;
}

int KM() {
	memset(linker, -1, sizeof(linker));
	memset(ly, 0, sizeof(ly));
	for (int i = 0; i < nx; i++) {
		lx[i] = -INF;
		for (int j = 0; j < ny; j++) {
			if (g[i][j] > lx[i]) { lx[i] = g[i][j]; }
		}
	}
	for (int x = 0; x < nx; x++) {
		memset(slack, 0x3f, sizeof(slack));
		while (true) {
			memset(visx, false, sizeof(visx));
			memset(visy, false, sizeof(visy));
			if (DFS(x)) { break; }
			int d = INF;
			for (int i = 0; i < ny; i++) {
				if (!visy[i] && d > slack[i]) { d = slack[i]; }
			}
			for (int i = 0; i < nx; i++) {
				if (visx[i]) { lx[i] -= d; }
			}
			for (int i = 0; i < ny; i++) {
				if (visy[i]) { ly[i] += d; }
				else { slack[i] -= d; }
			}
		}
	}
	int res = 0;
	for (int i = 0; i < ny; i++) {
		if (linker[i] != -1) { res += g[linker[i]][i]; }
	}
	return res;
}

//һ��ͼƥ�������
int n; //��ĸ��� ��ı�Ŵ�1��n
bool Graph[N][N];
int Match[N];
bool InQueue[N], InPath[N], InBlossom[N];
int Head, Tail;
int Queue[N];
int Start, Finish, NewBase;
int Father[N], Base[N];
int Count;//ƥ������ƥ�������Count/2
void CreateGraph() {
	int u, v;
	memset(Graph, false, sizeof(Graph));
	scanf("%d", &n);
	while (~scanf("%d%d", &u, &v)) {
		Graph[u][v] = Graph[v][u] = true;
	}
}

void Push(int u) {
	Queue[Tail] = u;
	Tail++;
	InQueue[u] = true;
}

int Pop() {
	int res = Queue[Head];
	Head++;
	return res;
}

int FindCommonAncestor(int u, int v) {
	memset(InPath, false, sizeof(InPath));
	while (true) {
		u = Base[u];
		InPath[u] = true;
		if (u == Start) { break; }
		u = Father[Match[u]];
	}
	while (true) {
		v = Base[v];
		if (InPath[v]) { break; }
		v = Father[Match[v]];
	}
	return v;
}

void ResetTrace(int u) {
	int v;
	while (Base[u] != NewBase) {
		v = Match[u];
		InBlossom[Base[u]] = InBlossom[Base[v]] = true;
		u = Father[v];
		if (Base[u] != NewBase) { Father[u] = v; }
	}
}

void BloosomContract(int u, int v) {
	NewBase = FindCommonAncestor(u, v);
	memset(InBlossom, false, sizeof(InBlossom));
	ResetTrace(u);
	ResetTrace(v);
	if (Base[u] != NewBase) { Father[u] = v; }
	if (Base[v] != NewBase) { Father[v] = u; }
	for (int tu = 1; tu <= n; tu++)
		if (InBlossom[Base[tu]]) {
			Base[tu] = NewBase;
			if (!InQueue[tu]) { Push(tu); }
		}
}

void FindAugmentingPath() {
	memset(InQueue, false, sizeof(InQueue));
	memset(Father, 0, sizeof(Father));
	for (int i = 1; i <= n; i++) { Base[i] = i; }
	Head = Tail = 1;
	Push(Start);
	Finish = 0;
	while (Head < Tail) {
		int u = Pop();
		for (int v = 1; v <= n; v++)
			if (Graph[u][v] && (Base[u] != Base[v]) && (Match[u] != v)) {
				if ((v == Start) || ((Match[v] > 0) && Father[Match[v]] > 0)) {
					BloosomContract(u, v);
				} else if (Father[v] == 0) {
					Father[v] = u;
					if (Match[v] > 0) { Push(Match[v]); }
					else { Finish = v; return; }
				}
			}
	}
}

void AugmentPath() {
	int u, v, w;
	u = Finish;
	while (u > 0) {
		v = Father[u]; w = Match[v];
		Match[v] = u; Match[u] = v;
		u = w;
	}
}

void Edmonds() {
	memset(Match, 0, sizeof(Match));
	for (int u = 1; u <= n; u++)
		if (Match[u] == 0) {
			Start = u;
			FindAugmentingPath();
			if (Finish > 0) { AugmentPath(); }
		}
}

void PrintMatch() {
	Count = 0;
	for (int u = 1; u <= n; u++)
		if (Match[u] > 0) { Count++; }
	printf("%d\n", Count);
	for (int u = 1; u <= n; u++) {
		if (u < Match[u]) { printf("%d %d\n", u, Match[u]); }
	}
}

int main() {
	CreateGraph();//��ͼ
	Edmonds();//����ƥ��
	PrintMatch();//���ƥ������ƥ��
}
