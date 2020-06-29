#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
char tmpc[1105];
typedef struct node {
	char s[1105];
	int num;
	struct node *nxt;
} node;
node *head;
node *find() {
	node *pos = head;
	while (pos->nxt != NULL && strcmp(tmpc, pos->nxt->s) > 0) pos = pos->nxt;
	return pos;
}
int main () {
	FILE *in = fopen("article.txt", "r");
	node *pos, *tmp;
	head = (node *) malloc(sizeof(node));
	char ch;
	int it = 0;
	while ((ch = fgetc(in)) != EOF) {
		ch = tolower(ch);
		if (!isalpha(ch) && it) {
			pos = find();
			if (pos->nxt != NULL && strcmp(pos->nxt->s, tmpc) == 0) pos->nxt->num++;
			else {
				tmp = pos;
				pos = (node *) malloc(sizeof(node));
				strcpy(pos->s, tmpc);
				pos->num = 1;
				pos->nxt = tmp->nxt;
				tmp->nxt = pos;
			}
			it = 0;
		} else if (isalpha(ch)) {
			tmpc[it++] = ch;
			tmpc[it] = '\0';
		}
	}
	for (pos = head->nxt; pos != NULL; pos = pos->nxt) {
		printf("%s %d\n", pos->s, pos->num);
	}
	fclose(in);
	return 0;
}


