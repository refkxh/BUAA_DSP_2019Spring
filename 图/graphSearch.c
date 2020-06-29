#include <stdio.h>
#include <string.h>
int front = 0, tail = 0, n;
int G[107][107], vis[107], q[1000007];
void dfs(int cur) {
	int i;
	if (cur) {
		vis[cur] = 1;
		printf(" %d", cur);
	}
	for (i = 0; i < n; i++) {
		if (G[cur][i] && !vis[i]) dfs(i);
	}
}
void bfs() {
	int i;
	q[tail++] = 0;
	while (front < tail) {
		if (q[front]) printf(" %d", q[front]);
		for (i = 0; i < n; i++) {
			if (G[q[front]][i] && !vis[i]) {
				q[tail++] = i;
				vis[i] = 1;
			}
		}
		front++;
	}
}
int main() {
	int m, i, tmp1, tmp2, del;
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &tmp1, &tmp2);
		G[tmp1][tmp2] = 1;
		G[tmp2][tmp1] = 1;
	}
	scanf("%d", &del);
	putchar('0');
	vis[0] = 1;
	dfs(0);
	putchar('\n');
	memset(vis, 0, sizeof(vis));
	vis[0] = 1;
	putchar('0');
	bfs();
	putchar('\n');
	for (i = 0; i < n; i++) {
		G[i][del] = 0;
		G[del][i] = 0;
	}
	memset(vis, 0, sizeof(vis));
	vis[0] = 1;
	putchar('0');
	dfs(0);
	putchar('\n');
	memset(vis, 0, sizeof(vis));
	vis[0] = 1;
	front = 0;
	tail = 0;
	putchar('0');
	bfs();
	putchar('\n');
	return 0;
}

