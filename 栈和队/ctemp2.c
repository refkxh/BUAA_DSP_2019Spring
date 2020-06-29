#include <stdio.h>
int q[1000007];
int front = 1, rear = 1;
int main() {
	int period = 0, n, i, j, num, windows = 3;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &num);
		while (num--) q[rear++] = i;
		while (windows < 5 && 7 * windows <= rear - front) windows++;
		for (j = 0; j < windows; j++) {
			if (front == rear) break;
			printf("%d : %d\n", front, period - q[front]);
			front++;
		}
		while (windows > 3 && 7 * windows > rear - front) windows--;
		period++;
	}
	while (front < rear) {
		for (i = 0; i < windows; i++) {
			if (front == rear) break;
			printf("%d : %d\n", front, period - q[front]);
			front++;
		}
		while (windows > 3 && 7 * windows > rear - front) windows--;
		period++;
	}
	return 0;
}

