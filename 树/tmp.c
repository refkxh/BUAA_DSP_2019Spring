#include <stdio.h>
#include <stdlib.h>
int freq[128], code[128], len[128];
typedef struct node {
	int key, dep;
	char ch;
	struct node *left, *right;
} node;
node *nodes[10007];
int front = 0, rear = 0, hex = 0, curl = 0;
int cmp(const void *pt1, const void *pt2) {
	const node * const *p1 = pt1, * const *p2 = pt2;
	if ((*p1)->key < (*p2)->key) return -1;
	else if ((*p1)->key == (*p2)->key) return (*p1)->ch - (*p2)->ch;
	else return 1;
}
void huffman(node *cur, int sum) {
	if (cur->ch == -1) {
		cur->left->dep = cur->dep + 1;
		huffman (cur->left, sum << 1);
		cur->right->dep = cur->dep + 1;
		huffman (cur->right, (sum << 1) + 1);
	}
	else {
		code[cur->ch] = sum;
		len[cur->ch] = cur->dep;
	}
}
void manip(int num, int len, int op) {
	while (len--) {
		if (curl == 8) {
			printf("%x", hex);
			hex = 0;
			curl = 0;
		}
		hex = (hex << 1) + (((num & (1 << len)) > 0) ? 1 : 0);
		curl++;
	}
	if (op) {
		while (curl < 8) {
			hex <<= 1;
			curl++;
		}
		printf("%x\n", hex);
	}
}
int main() {
	FILE *in = fopen("input.txt", "r"), *out = fopen("output.txt", "w");
	char ch;
	int i;
	node *tmp, *tmp2;
	freq[0] = 1;
	while ((ch = getc(in)) != EOF) {
		if (ch != '\n') freq[ch]++;
	}
	rewind(in);
	for (i = 0; i < 128; i++) {
		if (freq[i]) {
			nodes[rear] = (node *) malloc(sizeof(node));
			nodes[rear]->ch = i;
			nodes[rear]->key = freq[i];
			nodes[rear]->left = NULL;
			nodes[rear]->right = NULL;
			rear++;
		}
	}
	qsort(nodes, rear, sizeof(node *), cmp);
	while (rear - front > 1) {
		tmp = (node *) malloc(sizeof(node));
		tmp->ch = -1;
		tmp->key = nodes[front]->key + nodes[front + 1]->key;
		tmp->left = nodes[front++];
		tmp->right = nodes[front++];
		i = front;
		while (i < rear && nodes[i]->key <= tmp->key) i++;
		for (; i < rear; i++) {
			tmp2 = nodes[i];
			nodes[i] = tmp;
			tmp = tmp2;
		}
		nodes[rear++] = tmp;
	}
	nodes[front]->dep = 0;
	huffman(nodes[front], 0);
	while ((ch = getc(in)) != EOF) {
		if (ch != '\n') {
			putc(code[ch], out);
			manip(code[ch], len[ch], 0);
		}
	}
	putc(code[0], out);
	manip(code[0], len[0], 1);
	fclose(in);
	fclose(out);
	return 0;
}

