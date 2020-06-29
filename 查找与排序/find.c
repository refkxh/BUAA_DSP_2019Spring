#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NHASH 3001
#define MULT 37
char dic[3507][27], word[27];
int pos[26][2];
typedef struct node {
	char word[27];
	struct node *nxt;
} node;
node *head[3007];
node *cur, *tmpnode;
unsigned int hash(char *str) {
    unsigned int h = 0;
    char *p;
    for(p = str; *p != '\0'; p++) h = MULT * h + *p;
    return h % NHASH;
}
int main() {
	FILE *in = fopen("dictionary3000.txt", "r");
	int op, dicsize = 0, ans = 0, cmpcnt = 0, i, tmp, l, r, m, ha;
	while (fscanf(in, "%s", dic[dicsize]) != EOF) dicsize++;
	scanf("%s%d", word, &op);
	switch (op) {
		case 1:
			for (i = 0; i < dicsize; i++) {
				cmpcnt++;
				tmp = strcmp(word, dic[i]);
				if (tmp < 0) break;
				else if (tmp == 0) {
					ans = 1;
					break;
				}
			}
			break;
		case 2:
			l = 0;
			r = dicsize - 1;
			while (l <= r) {
				m = (l + r) >> 1;
				cmpcnt++;
				tmp = strcmp(word, dic[m]);
				if (tmp == 0) {
					ans = 1;
					break;
				}
				else if (tmp < 0) {
					r = m - 1;
					if (l < 0) l = 0;
				}
				else {
					l = m + 1;
					if (r > dicsize - 1) r = dicsize - 1;
				}
			}
			break;
		case 3:
			for (i = 0; i < dicsize; i++) {
				if (i == 0 || dic[i][0] != dic[i - 1][0]) pos[dic[i][0] - 'a'][0] = i;
				pos[dic[i][0] - 'a'][1]++;
			}
			l = pos[word[0] - 'a'][0];
			r = l + pos[word[0] - 'a'][1] - 1;
			while (l <= r) {
				m = (l + r) >> 1;
				cmpcnt++;
				tmp = strcmp(word, dic[m]);
				if (tmp == 0) {
					ans = 1;
					break;
				}
				else if (tmp < 0) {
					r = m - 1;
					if (l < 0) l = 0;
				}
				else {
					l = m + 1;
					if (r > dicsize - 1) r = dicsize - 1;
				}
			}
			break;
		case 4:
			for (i = 0; i < dicsize; i++) {
				ha = hash(dic[i]);
				if (head[ha] == NULL) {
					head[ha] = (node *) malloc(sizeof(node));
					strcpy(head[ha]->word, dic[i]);
					head[ha]->nxt = NULL;
				}
				else {
					cur = head[ha];
					while (cur->nxt != NULL) cur = cur->nxt;
					tmpnode = (node *) malloc(sizeof(node));
					strcpy(tmpnode->word, dic[i]);
					tmpnode->nxt = NULL;
					cur->nxt = tmpnode;
				}
			}
			ha = hash(word);
			cur = head[ha];
			while (cur != NULL) {
				cmpcnt++;
				tmp = strcmp(word, cur->word);
				if (tmp < 0) break;
				else if (tmp == 0) {
					ans = 1;
					break;
				}
				cur = cur->nxt;
			}
	}
	printf("%d %d\n", ans, cmpcnt);
	fclose(in);
	return 0;
}

