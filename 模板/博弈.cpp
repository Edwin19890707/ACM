//Nim����
//�����1-n��Χ�ڵ�SGֵ
//Array�洢�����ߵĲ�����Array[0]��ʾ�����ж������߷�
//Array[]��Ҫ��С��������
//HDU1847 ����SG����
//1.��ѡ����Ϊ1-m������������ֱ��ȡģ���ɣ�SG(x) = x % (m + 1);
//2.��ѡ����Ϊ���ⲽ��SG(x) = x;
//3.��ѡ����Ϊһϵ�в�������������GetSG(����)
int SG[N], Hash[N];

void GetSG(int Array[], int n = N - 1) {
	memset(SG, 0, sizeof(SG));
	for (int i = 0; i <= n; ++i) {
		memset(Hash, 0, sizeof(Hash));
		for (int j = 1; j <= Array[0]; j++) {
			if (i < Array[j]) { break; }
			Hash[SG[i - Array[j]]] = 1;
		}
		for (int j = 0; j <= n; j++) {
			if (!Hash[j]) { SG[i] = j; break; }
		}
	}
}
