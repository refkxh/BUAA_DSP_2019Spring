#include <stdio.h>
#include <stdlib.h>
int a[2007][2], b[2007][2];
typedef struct node {
	int num, exp;
	struct node *nxt;
} node;
int main() {
	int na = 0, nb = 0, tnum, texp, i, j;
	char ch;
	node *head = (node*) malloc(sizeof(node)), *cur, *tmp;
	head->exp = 1e9+7;
	head->nxt = head;
	do {
		scanf("%d%d", &a[na][0], &a[na][1]);
		na++;
		ch = getchar();
	} while (ch != '\n');
	while (scanf("%d%d", &b[nb][0], &b[nb][1]) != EOF) nb++;
	for (i = 0; i < na; i++) {
		for (j = 0; j < nb; j++) {
			tnum = a[i][0] * b[j][0];
			texp = a[i][1] + b[j][1];
			cur = head->nxt;
			while (cur->nxt->exp > texp && cur->nxt != head) cur = cur->nxt;
			if (cur->nxt->exp == texp) cur->nxt->num += tnum;
			else {
				tmp = (node*) malloc(sizeof(node));
				tmp->exp = texp;
				tmp->num = tnum;
				tmp->nxt = cur->nxt;
				cur->nxt = tmp;
			}
		}
	}
	cur = head->nxt;
	while (cur != head) {
		printf("%d %d ", cur->num, cur->exp);
		cur = cur->nxt;
	}
	printf("\n");
	return 0;
}


