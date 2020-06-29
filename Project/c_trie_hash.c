#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ll {
	int val;
	struct ll *nxt;
} ll;

typedef struct trienode {  
    int exist;
    struct trienode *nxt[26];
} trienode;

typedef struct node {
	char w[57];
	int key, nxt;
} node;

typedef struct ansnode {
	char w[57];
	int freq;
	ll *head, *tail;
} ansnode;

FILE *dic, *in, *out;
int num = 0, nodecnt = 0, ha, len;
char tmp[57], buf[65536];
int head[100007];
trienode *root;
node nodes[25007];
ansnode ans[25007];

char mgetc(FILE *f) {
    static char *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 65536, f), p1 == p2) ? EOF : *p1++;
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
	int cnt = 0, i;
	trienode *cur = root;

	while ((ch = mgetc(dic)) != EOF) {
		if (ch >= 'a' && ch <= 'z') {
			cnt++;
			ch -= 'a';
			if (cur->nxt[ch] == NULL) {
				cur->nxt[ch] = (trienode *) malloc(sizeof(trienode));
				cur = cur->nxt[ch];
				cur->exist = 0;
				for (i = 0; i < 26; i++) {
					cur->nxt[i] = NULL;
				}
			}
			else cur = cur->nxt[ch];
		}
		else if (cnt) {
			cur->exist = 1;
			break;
		}
	}

	return cnt;
}


int triesearch() {

	char ch;
	int i = 0;
	trienode *cur = root;

	while (i < len) {
		ch = tmp[i] - 'a';
		
		if (cur->nxt[ch] != NULL) {
			cur = cur->nxt[ch];
			i++;
		}
		else return 0;
	}

	if (cur->exist == 1) return 1;
	else return 0;
}

int hash() {

    int h = 0;
    char *p;

    for (p = tmp; *p != '\0'; p++) h = 27 * h % 100007 + *p - 96;

    return h % 100007;
}

void ins(int key) {

	int tmpnode;

	if (head[ha] == 0) {
		head[ha] = ++nodecnt;
		strcpy(nodes[head[ha]].w, tmp);
		nodes[head[ha]].key = key;
		nodes[head[ha]].nxt = 0;
	}
	else {
		tmpnode = ++nodecnt;
		strcpy(nodes[tmpnode].w, tmp);
		nodes[tmpnode].key = key;
		nodes[tmpnode].nxt = nodes[head[ha]].nxt;
		nodes[head[ha]].nxt = tmpnode;
	}
}

int find() {

	int cur;
	ha = hash();
	cur = head[ha];

	while (cur != 0) {
		if (strcmp(tmp, nodes[cur].w) == 0) return cur;
		cur = nodes[cur].nxt;
	}

	return 0;
}

int cmp(const void *pt1, const void *pt2) {

	const ansnode *p1 = pt1, *p2 = pt2;

	if (p1->freq > p2->freq) return -1;
	else if (p1->freq == p2->freq && strcmp(p1->w, p2->w) < 0) return -1;
	else return 1;
}

int main() {

	int pos = 0, anscnt = 0, i;
	ll *tp;

	dic = fopen("dictionary.txt", "r");
	in = fopen("article.txt", "r");
	out = fopen("misspelling.txt", "w");
	
	root = (trienode *) malloc(sizeof(trienode));
	root->exist = 0;
	for (i = 0; i < 26; i++) {
		root->nxt[i] = NULL;
	}

	while (readDict());

	while (len = readWord()) {

		int key, tmpnode;

		pos += num - 1;

		if (!triesearch()) {

			tmpnode = find();

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

	qsort(ans, anscnt, sizeof(ansnode), cmp);

	for (i = 0; i < anscnt; i++) {
		fprintf(out, "%s %d", ans[i].w, ans[i].freq);
		tp = ans[i].head;
		do {
			fprintf(out, " %d", tp->val);
			tp = tp->nxt;
		} while (tp != ans[i].head);
		putc('\n', out);
	}

	fclose(dic);
	fclose(in);
	fclose(out);

	return 0;
}


