#include <stdio.h>
typedef struct node {
	int ecnt;
	int to[1007], edge[1007];
} node;
int n, anslen = 0;
int ans[1007], vis[1007];
node nodes[1007];
void dfs(int cur) {
	int i;
	vis[cur] = 1;
	if (cur == n - 1) {
		printf("%d", ans[0]);
		for (i = 1; i < anslen; i++) {
			printf(" %d", ans[i]);
		}
		putchar('\n');
	}
	else {
		for (i = 0; i < nodes[cur].ecnt; i++) {
			if (!vis[nodes[cur].to[i]]) {
				ans[anslen++] = nodes[cur].edge[i];
				dfs(nodes[cur].to[i]);
				anslen--;
			}
		}
	}
	vis[cur] = 0;
}
int main() {
	int e, tmp1, tmp2, tmp3;
	scanf("%d%d", &n, &e);
	while (e--) {
		scanf("%d%d%d", &tmp1, &tmp2, &tmp3);
		nodes[tmp2].edge[nodes[tmp2].ecnt] = tmp1;
		nodes[tmp2].to[nodes[tmp2].ecnt++] = tmp3;
		nodes[tmp3].edge[nodes[tmp3].ecnt] = tmp1;
		nodes[tmp3].to[nodes[tmp3].ecnt++] = tmp2;
	}
	dfs(0);
	return 0;
}

