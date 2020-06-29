#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct node {
	int val, isop;
	struct node *left, *right;
} node;
int ex[2007], isop[2007];
char ops[2007];
node *nodes[2007];
int extop = 0, opstop = 0, nodestop = 0;
int inOrder(node *cur) {
	if (cur->isop) {
		if (cur->val == '+') return inOrder(cur->left) + inOrder(cur->right);
		else if (cur->val == '-') return inOrder(cur->left) - inOrder(cur->right);
		else if (cur->val == '*') return inOrder(cur->left) * inOrder(cur->right);
		else if (cur->val == '/') return inOrder(cur->left) / inOrder(cur->right);
	}
	else return cur->val;
}
int main() {
	char ch;
	int num = 0, flag = 0, i;
	node *tmp;
	while (1) {
		ch = getchar();
		if (ch == '+' || ch == '-') {
			if (flag) {
				ex[extop] = num;
				isop[extop] = 0;
				extop++;
				num = 0;
				flag = 0;
			}
			while (opstop && ops[opstop - 1] != '(') {
				ex[extop] = ops[--opstop];
				isop[extop] = 1;
				extop++;
			}
			ops[opstop++] = ch;
		}
		else if (ch == '*' || ch == '/') {
			if (flag) {
				ex[extop] = num;
				isop[extop] = 0;
				extop++;
				num = 0;
				flag = 0;
			}
			while (opstop && ops[opstop - 1] != '(' && ops[opstop - 1] != '+' && ops[opstop - 1] != '-') {
				ex[extop] = ops[--opstop];
				isop[extop] = 1;
				extop++;
			}
			ops[opstop++] = ch;
		}
		else if (ch == '(') ops[opstop++] = ch;
		else if (ch == ')') {
			if (flag) {
				ex[extop] = num;
				isop[extop] = 0;
				extop++;
				num = 0;
				flag = 0;
			}
			while (opstop && ops[opstop - 1] != '(') {
				ex[extop] = ops[--opstop];
				isop[extop] = 1;
				extop++;
			}
			if (opstop) opstop--;
		}
		else if (isdigit(ch)) {
			num = num * 10 + ch - '0';
			flag = 1;
		}
		else if (ch == '=') {
			if (flag) {
				ex[extop] = num;
				isop[extop] = 0;
				extop++;
			}
			while (opstop) {
				ex[extop] = ops[--opstop];
				isop[extop] = 1;
				extop++;
			}
			break;
		}
	} 
	for (i = 0; i < extop; i++) {
		if (isop[i]) {
			tmp = (node *) malloc(sizeof(node));
			tmp->isop = 1;
			tmp->val = ex[i];
			tmp->left = nodes[nodestop - 2];
			tmp->right = nodes[nodestop - 1];
			nodes[nodestop - 2] = tmp;
			nodestop--;
		}
		else {
			nodes[nodestop] = (node *) malloc(sizeof(node));
			nodes[nodestop]->isop = 0;
			nodes[nodestop]->val = ex[i];
			nodes[nodestop]->left = NULL;
			nodes[nodestop]->right = NULL;
			nodestop++;
		}
	}
	printf("%c", nodes[0]->val);
	if (nodes[0]->left != NULL) {
		if (nodes[0]->left->isop) printf(" %c", nodes[0]->left->val);
		else printf(" %d", nodes[0]->left->val);
	}
	if (nodes[0]->right != NULL) {
		if (nodes[0]->right->isop) printf(" %c", nodes[0]->right->val);
		else printf(" %d", nodes[0]->right->val);
	}
	putchar('\n');
	printf("%d\n", inOrder(nodes[0]));
	return 0;
}

