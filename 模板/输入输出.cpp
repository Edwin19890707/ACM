//����һ������
//G++ ONLY?
template <class T> inline bool getInt(T &x) {
  char c = 0; T sign = 1;
  if ((c = getchar()) == EOF) { return false; }
  while ((c < '0' || c > '9') && c != '-') { c = getchar(); };
  if (c == '-') { sign = -1; c = getchar(); }
  x = c - '0';
  while ((c = getchar()) >= '0' && c <= '9') { x = x * 10 + c - '0'; }
  x *= sign;
  return true;
}

//�ո���Ϊ�ָ� ��ȡһ�е�����
void getLine(int a[]) {
  int i = 0;
  gets(buf);
  for (char *p = strtok(buf, " "); p; p = strtok(NULL, " ")) {
    sscanf(p, "%d", &a[i++]);
  }
}

//���һ������
template <class T> inline void printInt(T x) {
  if (x > 9) { printInt(x / 10); }
  putchar(x % 10 + '0');
}
