#include <stdio.h>
#include <string.h>
int stationcnt;
char s1[107], s2[107], station[1007][107];
int G[1007][1007], vis[1007], dis[1007], prev[1007], ansstation[1007];
int find(char *s) {
	int i;
	for (i = 0; i < stationcnt; i++) {
		if (!strcmp(s, station[i])) return i;
	}
	return -1;
}
int main() {
	FILE *in = fopen("bgstations.txt", "r");
	int n, id, stationnum, i, j, op, f, start, ed, anscnt = 0, cur, mn, tmp, t, lat;
	memset(dis, 0x7f, sizeof(dis));
	fscanf(in, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(in, "%d%d", &id, &stationnum);
		for (j = 0; j < stationnum; j++) {
			fscanf(in, "%s%d", station[stationcnt], &op);
			f = find(station[stationcnt]);
			if (f < 0) f = stationcnt;
			if (j) {
				G[f][tmp] = id;
				G[tmp][f] = id;
			}
			stationcnt++;
			tmp = find(station[stationcnt - 1]);
		}
	}
	scanf("%s%s", s1, s2);
	start = find(s1);
	ed = find(s2);
	cur = start;
	dis[cur] = 0;
	t = stationcnt;
	while (t--) {
		vis[cur] = 1;
		for (i = 0; i < stationcnt; i++) {
			if (G[cur][i] && !vis[i] && dis[i] > dis[cur] + 1) {
				prev[i] = cur;
				dis[i] = dis[cur] + 1;
			}
		}
		mn = 10007;
		for (i = 0; i < stationcnt; i++) {
			if (dis[i] < mn && !vis[i]) {
				cur = i;
				mn = dis[i];
			}
		}
	}
	lat = ed;
	for (i = prev[ed]; i != start; i = prev[i]) {
		if (G[i][prev[i]] != G[lat][i]) ansstation[++anscnt] = i;
		lat = prev[lat];
	}
	ansstation[0] = ed;
	ansstation[anscnt + 1] = start;
	printf("%s", s1);
	for (i = anscnt; i >= 0; i--) {
		printf("-%d(%d)-%s", G[prev[ansstation[i]]][ansstation[i]], dis[ansstation[i]] - dis[ansstation[i + 1]], station[ansstation[i]]);
	}
	putchar('\n');
	fclose(in);
	return 0;
}


