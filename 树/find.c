#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char tmp1[27], tmp2[27], tmp3[27];
typedef struct node {
	char nam[27];
	int dep;
	struct node *p, *l, *r;
} node;
node *root = NULL;
node *q[10007];
int front = 0, rear = 0;
node *find(char *s, node *cur) {
	node *tmpnode;
	if (strcmp(s, cur->nam) == 0) return cur;
	if (cur->l != NULL) {
		tmpnode = find(s, cur->l);
		if (tmpnode != NULL) return tmpnode;
	}
	if (cur->r != NULL) {
		tmpnode = find(s, cur->r);
		if (tmpnode != NULL) return tmpnode;
	}
	return NULL;
}
int main() {
	FILE *in = fopen("in.txt", "r");
	int n, i;
	node *pt1, *pt2, *tmpnode1, *tmpnode2;
	fscanf(in, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(in, "%s%s%s", tmp1, tmp2, tmp3);
		if (root == NULL) {
			root = (node *) malloc(sizeof(node));
			strcpy(root->nam, tmp1);
			root->dep = 1;
			root->p = NULL;
			root->l = (node *) malloc(sizeof(node));
			strcpy(root->l->nam, tmp2);
			root->l->dep = 2;
			root->l->p = root;
			root->l->l = NULL;
			root->l->r = NULL;
			q[rear++] = root->l;
			if (strcmp(tmp3, "NULL") != 0) {
				root->r = (node *) malloc(sizeof(node));
				strcpy(root->r->nam, tmp3);
				root->r->dep = 2;
				root->r->p = root;
				root->r->l = NULL;
				root->r->r = NULL;
				q[rear++] = root->r;
			}
		}
		else {
			while (strcmp(tmp1, q[front]->nam) != 0) front++;
			q[front]->l = (node *) malloc(sizeof(node));
			strcpy(q[front]->l->nam, tmp2);
			q[front]->l->dep = q[front]->dep + 1;
			q[front]->l->p = q[front];
			q[front]->l->l = NULL;
			q[front]->l->r = NULL;
			q[rear++] = q[front]->l;
			if (strcmp(tmp3, "NULL") != 0) {
				q[front]->r = (node *) malloc(sizeof(node));
				strcpy(q[front]->r->nam, tmp3);
				q[front]->r->dep = q[front]->dep + 1;
				q[front]->r->p = q[front];
				q[front]->r->l = NULL;
				q[front]->r->r = NULL;
				q[rear++] = q[front]->r;
			}
			front++;
		}
	}
	scanf("%s%s", tmp1, tmp2);
	pt1 = find(tmp1, root);
	pt2 = find(tmp2, root);
	if (pt1->dep != pt2->dep) {
		if (pt1->dep < pt2->dep) {
			tmpnode1 = pt1;
			pt1 = pt2;
			pt2 = tmpnode1;
		}
		printf("%s %s %d\n", pt1->nam, pt2->nam, pt1->dep - pt2->dep);
	}
	else {
		tmpnode1 = pt1;
		tmpnode2 = pt2;
		while (tmpnode1 != tmpnode2) {
			tmpnode1 = tmpnode1->p;
			tmpnode2 = tmpnode2->p;
		}
		printf("%s %s %d\n", tmpnode1->nam, pt1->nam, pt1->dep - tmpnode1->dep);
		printf("%s %s %d\n", tmpnode2->nam, pt2->nam, pt2->dep - tmpnode2->dep);
	}
	fclose(in); 
	return 0;
}

