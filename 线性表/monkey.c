#include <stdio.h>
#include <stdlib.h>
typedef struct monkey {
	int num;
	struct monkey *nxt;
} monkey;
int main() {
	int n, m, q, i;
	monkey *head = (monkey*) malloc(sizeof(monkey)), *cur = head, *tmp;
	scanf("%d%d%d", &n, &m, &q);
	for (i = 1; i <= n; i++) {
		cur->num = i;
		if (i < n) {
			cur->nxt = (monkey*) malloc(sizeof(monkey));
			cur = cur->nxt;
		}
	}
	cur->nxt = head;
	for (i = 0; i < q; i++) {
		cur = cur->nxt;
	}
	while (cur != cur->nxt) {
		for (i = 1; i < m - 1; i++) {
			cur = cur->nxt;
		}
		tmp = cur->nxt;
		cur->nxt = cur->nxt->nxt;
		free(tmp);
		cur = cur->nxt;
	}
	printf("%d\n", cur->num);
	return 0;
}


