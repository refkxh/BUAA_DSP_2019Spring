#include <stdio.h>
#include <stdlib.h>
typedef struct edge {
	int id, u, v, w;
} edge;
int p[10007], ans[10007];
edge edges[10007];
int find(int x) {
	return x == p[x] ? x : (p[x] = find(p[x]));
}
int cmp1(const void *pt1, const void *pt2) {
	const edge *p1 = pt1, *p2 = pt2;
	return p1->w - p2->w;
}
int cmp2(const void *pt1, const void *pt2) {
	const int *p1 = pt1, *p2 = pt2;
	return *p1 - *p2;
}
int main() {
	int n, e, i, tmp1, tmp2, tmp3, tmp4, anscnt = 0, ansnum = 0, f1, f2;
	scanf("%d%d", &n, &e);
	for (i = 0; i < n; i++) {
		p[i] = i;
	}
	for (i = 0; i < e; i++) {
		scanf("%d%d%d%d", &tmp1, &tmp2, &tmp3, &tmp4);
		edges[i].id = tmp1;
		edges[i].u = tmp2;
		edges[i].v = tmp3;
		edges[i].w = tmp4;
	}
	qsort(edges, e, sizeof(edge), cmp1);
	for (i = 0; i < e; i++) {
		f1 = find(edges[i].u);
		f2 = find(edges[i].v);
		if (f1 != f2) {
			p[f2] = f1;
			ans[anscnt++] = edges[i].id;
			ansnum += edges[i].w;
		}
	}
	qsort(ans, anscnt, sizeof(int), cmp2);
	printf("%d\n", ansnum);
	printf("%d", ans[0]);
	for (i = 1; i < anscnt; i++) {
		printf(" %d", ans[i]);
	}
	putchar('\n');
	return 0;
}

