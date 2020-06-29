#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char tmp[57];
FILE *in;
typedef struct node {
	int freq;
	char word[57];
	struct node *left, *right;
} node;
node *root = NULL;
int readWord() {
	int pos = 0;
	char ch;
	while ((ch = getc(in)) != EOF) {
		if (isalpha(ch)) tmp[pos++] = tolower(ch);
		else if (pos) break;
	}
	tmp[pos] = '\0';
	return pos;
}
void ins() {
	node *cur = root, *tmpnode;
	if (root == NULL) {
		root = (node *) malloc(sizeof(node));
		strcpy(root->word, tmp);
		root->freq = 1;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		while (1) {
			if (strcmp(tmp, cur->word) == 0) {
				cur->freq++;
				break;
			}
			else if (strcmp(tmp, cur->word) < 0) {
				if (cur->left != NULL) cur = cur->left;
				else {
					tmpnode = (node *) malloc(sizeof(node));
					strcpy(tmpnode->word, tmp);
					tmpnode->freq = 1;
					tmpnode->left = NULL;
					tmpnode->right = NULL;
					cur->left = tmpnode;
					break;
				}
			}
			else {
				if (cur->right != NULL) cur = cur->right;
				else {
					tmpnode = (node *) malloc(sizeof(node));
					strcpy(tmpnode->word, tmp);
					tmpnode->freq = 1;
					tmpnode->left = NULL;
					tmpnode->right = NULL;
					cur->right = tmpnode;
					break;
				}
			}
		}
	}
}
void inOrder(node *cur) {
	if (cur->left != NULL) inOrder(cur->left);
	printf("%s %d\n",cur->word, cur->freq);
	if (cur->right != NULL) inOrder(cur->right);
}
int main() {
	in = fopen("article.txt", "r");
	while (readWord()) ins();
	printf("%s", root->word);
	if (root->right != NULL) printf(" %s", root->right->word);
	if (root->right->right != NULL) printf(" %s", root->right->right->word);
	putchar('\n');
	inOrder(root);
	fclose(in);
	return 0;
}

