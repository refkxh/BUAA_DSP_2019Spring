#include <stdio.h>
#include <stdlib.h>
typedef struct node {
	int val, dep;
	struct node *left, *right;
} node;
node *root = NULL;
void ins(int key) {
	int dep = 1;
	node *tmp = (node *) malloc(sizeof(node)), *cur = root;
	tmp->val = key;
	tmp->left = NULL;
	tmp->right = NULL;
	if (root == NULL) {
		root = tmp;
		tmp->dep = 1;
	}
	else {
		while (1) {
			if (key < cur->val) {
				if (cur->left != NULL) {
					dep++;
					cur = cur->left;
				}
				else {
					tmp->dep = dep + 1;
					cur->left = tmp;
					break;
				}
			}
			else {
				if (cur->right != NULL) {
					dep++;
					cur = cur->right;
				}
				else {
					tmp->dep = dep + 1;
					cur->right = tmp;
					break;
				}
			}
		}
	}
}
void dfs(node *cur) {
	if (cur->left == NULL && cur->right == NULL) {
		printf("%d %d\n", cur->val, cur->dep);
		return;
	}
	if (cur->left != NULL) dfs(cur->left);
	if (cur->right != NULL) dfs(cur->right); 
}
int main() {
	int n, tmp;
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &tmp);
		ins(tmp);
	}
	dfs(root);
	return 0;
}

