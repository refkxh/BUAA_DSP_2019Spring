#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char s[40], crypt[200], vis[200];
typedef struct node {
	char c;
	struct node *nxt;
} node;
int main() {
	char ch;
	int len, i, num;
	FILE *in = fopen("in.txt", "r"), *out = fopen("in_crpyt.txt", "w");
	node *head = (node*) malloc(sizeof(node)), *cur = head, *tmp, *tmp2;
	scanf("%[^\n]", s);
	len = strlen(s);
	head->c = s[0];
	vis[s[0]]=1;
	for (i = 1; i < len; i++) {
		if (!vis[s[i]]) {
			vis[s[i]] = 1;
			tmp = (node*) malloc(sizeof(node));
			tmp->c = s[i];
			cur->nxt = tmp;
			cur = tmp;
		}
	}
	for (i = 32; i <= 126; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			tmp = (node*) malloc(sizeof(node));
			tmp->c = i;
			cur->nxt = tmp;
			cur = tmp;
		}
	}
	cur->nxt = head;
	tmp2 = cur;
	cur = head;
	while (cur->nxt != cur) {
		num = cur->c;
		tmp = cur;
		cur = cur->nxt;
		tmp2->nxt = cur;
		free(tmp);
		for (i = 1; i < num; i++) {
			cur = cur->nxt;
			tmp2 = tmp2->nxt;
		}
		crypt[num] = cur->c;
	}
	crypt[cur->c] = s[0];
	while ((ch = getc(in)) != EOF) {
		if (ch >= 32 && ch <= 126) putc(crypt[ch], out);
		else putc(ch, out);
	}
	fclose(in);
	fclose(out);
	return 0;
}


