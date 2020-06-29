#include <stdio.h>
int st[100];
int pos = 0;
int main() {
	int op, tmp;
	while (1) {
		scanf("%d", &op);
		switch (op) {
			case 1:
				scanf("%d", &tmp);
				if (pos == 100) printf("error ");
				else st[pos++] = tmp;
				break;
			case 0:
				if (pos == 0) printf("error ");
				else printf("%d ", st[--pos]);
				break;
			case -1:
				putchar('\n');
				return 0;
		}
	}
}

