#include <stdio.h>
#include <stdlib.h>
int vis[107];
typedef struct stu {
	int num, seat;
	char nam[27];
} stu;
stu students[107];
int cmp1(const void *pt1, const void *pt2) {
	const stu *p1 = pt1, *p2 = pt2;
	if (p1->seat < p2->seat) return -1;
	else if (p1->seat == p2->seat) return p1->num - p2->num;
	else return 1;
}
int cmp2(const void *pt1, const void *pt2) {
	const stu *p1 = pt1, *p2 = pt2;
	return p1->num - p2->num;
}
int main() {
	FILE *in = fopen("in.txt", "r"), *out = fopen("out.txt", "w");
	int stucnt, i, tail, m, q;
	scanf("%d", &stucnt);
	tail = stucnt - 1;
	for (i = 0; i < stucnt; i++) {
		fscanf(in, "%d%s%d", &students[i].num, students[i].nam, &students[i].seat);
	}
	qsort(students, stucnt, sizeof(stu), cmp1);
	for (i = 0; i < stucnt; i++) {
		vis[students[i].seat] = 1;
	}
	q = stucnt;
	if (students[stucnt - 1].seat < q) q = students[stucnt - 1].seat;
	for (i = 1; i <= q; i++) {
		if (!vis[i] && students[tail - 1].seat > i) students[tail--].seat = i;
	}
	qsort(students, stucnt, sizeof(stu), cmp1);
	m = students[stucnt - 1].seat + 1;
	for (i = 0; i < stucnt; i++) {
		if (students[i].seat == students[i - 1].seat) {
			students[i].seat = m;
			m++;
		}
	}
	qsort(students, stucnt, sizeof(stu), cmp2);
	for (i = 0; i < stucnt; i++) {
		fprintf(out, "%d %s %d\n", students[i].num, students[i].nam, students[i].seat);
	}
	fclose(in);
	fclose(out);
	return 0;
}


