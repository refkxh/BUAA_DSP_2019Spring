#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ll {
	int val;
	struct ll *nxt;
} ll;

typedef struct node {
	char w[37];
	int key, left, right;
} node;

typedef struct ansnode {
	char w[37];
	int freq;
	ll *head, *tail;
} ansnode;

FILE *dic, *in, *out;
int num = 0, dictsize = 0, root = 0, nodecnt = 0;
char dict[420007][37], tmp[37], buf[1000007];
node nodes[2407];
ansnode ans[2407];

char mgetc(FILE *f) {
    static char *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000007, f), p1 == p2) ? EOF : *p1++;
}

int readWord() {

	char ch;
	int cnt = 0;
	num = 0;

	while ((ch = mgetc(in)) != EOF) {
		if (ch >= 'a' && ch <= 'z') tmp[cnt++] = ch;
		else if (ch >= 'A' && ch <= 'Z') tmp[cnt++] = ch + 32;
		else {
			num++;
			if (cnt) break;
		}
	}
	tmp[cnt] = '\0';

	return cnt;
}

int readDict() {

	char ch;
	int cnt = 0;

	while ((ch = mgetc(dic)) != EOF) {
		if (ch >= 'a' && ch <= 'z') dict[dictsize][cnt++] = ch;
		else if (cnt) break;
	}
	dict[dictsize][cnt] = '\0';

	return cnt;
}

void ins(int key) {

	int fa = 0, cur = root, n = ++nodecnt;

	strcpy(nodes[n].w, tmp);
	nodes[n].key = key;
	nodes[n].left = 0;
	nodes[n].right = 0;

	while (cur != 0) {
		fa = cur;
		if (strcmp(tmp, nodes[cur].w) < 0) cur = nodes[cur].left;
		else cur = nodes[cur].right;
	}

	if (fa == 0) root = n;
	else if (strcmp(tmp, nodes[fa].w) < 0) nodes[fa].left = n;
	else nodes[fa].right = n;
}

int find(int cur) {

	int val;

	while (cur != 0 && (val = strcmp(tmp, nodes[cur].w)) != 0) {
		if (val < 0) cur = nodes[cur].left;
		else cur = nodes[cur].right;
	}

	return cur;
}

int cmpb(const void *pt1, const void *pt2) {
	const char *p1 = pt1, *p2 = pt2;
	return strcmp(p1, p2);   
}

int cmpq(const void *pt1, const void *pt2) {

	const ansnode *p1 = pt1, *p2 = pt2;

	if (p1->freq > p2->freq) return -1;
	else if (p1->freq == p2->freq && strcmp(p1->w, p2->w) < 0) return -1;
	else return 1;
}

int main() {

	int pos = 0, anscnt = 0, len, i;
	ll *tp;

	dic = fopen("dictionary.txt", "r");
	in = fopen("article.txt", "r");
	out = fopen("misspelling.txt", "w");

	while (readDict()) dictsize++;

	while (len = readWord()) {

		int key, tmpnode;

		pos += num - 1;

		if (bsearch(tmp, dict, dictsize, sizeof(tmp), cmpb) == NULL) {

			tmpnode = find(root);

			if (tmpnode != 0) {
				key = nodes[tmpnode].key;
				tp = ans[key].tail;
				ans[key].tail = (ll *) malloc(sizeof(ll));
				ans[key].tail->val = pos;
				ans[key].tail->nxt = ans[key].head;
				tp->nxt = ans[key].tail;
				ans[key].freq++;
			}
			else {
				ins(anscnt);
				ans[anscnt].freq = 1;
				ans[anscnt].head = (ll *) malloc(sizeof(ll));
				ans[anscnt].head->val = pos;
				ans[anscnt].head->nxt = ans[anscnt].head;
				ans[anscnt].tail = ans[anscnt].head;
				strcpy(ans[anscnt].w, tmp);
				anscnt++;
			}
		}

		pos += len + 1;

	}

	qsort(ans, anscnt, sizeof(ansnode), cmpq);

	for (i = 0; i < anscnt; i++) {
		fprintf(out, "%s %d", ans[i].w, ans[i].freq);
		tp = ans[i].head;
		do {
			fprintf(out, " %d", tp->val);
			tp = tp->nxt;
		} while (tp != ans[i].head);
		fprintf(out, "\n");
	}

	fclose(dic);
	fclose(in);
	fclose(out);

	return 0;
}
