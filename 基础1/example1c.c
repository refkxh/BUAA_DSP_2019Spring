#include <stdio.h>
#define MAXN 1000005
int num[MAXN];
int main() {
	int pt = 0, n;
	char op;
	scanf("%d", &num[pt++]);
	while (1) {
		op = getchar();
		if (op == '=') break;
		else if (op == ' ') continue;
		scanf("%d", &n);
		if (op == '*' || op == '/') {
			if (op == '*') num[pt - 1] *= n;
			else num[pt - 1] /= n;
			op = 0;
		}
		else num[pt++] = (op == '+' ? n : -n);
	}
	while (pt > 1) {
		num[pt - 2] += num[pt - 1];
		pt--;
	}
	printf("%d\n", num[0]);
	return 0;
}


