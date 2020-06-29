#include <stdio.h>
int cmpcnt = 0;
int a[107], tmp[107];
void swap(int *p1, int *p2) {
	int t = *p1;
	*p1 = *p2;
	*p2 = t;
}
void adjust(int i, int n) {
    int j, temp;
    temp = a[i];
    j = 2 * i + 1;
    while(j < n) {
        if(j < n - 1 && a[j] < a[j + 1]) j++;
        cmpcnt++;
        if(temp >= a[j]) break;
        a[(j - 1) / 2] = a[j];
        j = 2 * j + 1;
    }
    a[(j - 1) / 2] = temp;
}
void merge(int left, int leftend, int rightend) {
    int i = left, j = leftend + 1, q = left;
    while(i <= leftend && j <= rightend) {
    	cmpcnt++;
        if(a[i] <= a[j]) tmp[q++] = a[i++];
        else tmp[q++] = a[j++];
    }
    while(i <= leftend) tmp[q++] = a[i++];
    while(j <= rightend) tmp[q++] = a[j++];
    for(i = left; i <= rightend; i++) a[i] = tmp[i];
}
void mergeSort(int l, int r) {
	int mid = (l + r) >> 1;
	if (l == r) return;
	mergeSort(l, mid);
	mergeSort(mid + 1, r);
	merge(l, mid, r);
}
void quickSort(int l,int r) {
    int i, last;
    if(l < r){
        last = l;
        for(i = l + 1; i <= r; i++) {
        	cmpcnt++;
        	if(a[i] < a[l]) swap(&a[++last], &a[i]);
		}
        swap(&a[l], &a[last]);
        quickSort(l, last - 1);
        quickSort(last + 1, r);
    }
}
int main() {
	int n, op, i, j, flag, minpos;
	scanf("%d%d", &n, &op);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	switch (op) {
		case 1:
			for (i = 0; i < n; i++) {
				minpos = i;
				for (j = i + 1; j < n; j++) {
					cmpcnt++;
					if (a[j] < a[minpos]) minpos = j;
				}
				swap(&a[i], &a[minpos]);
			}
			break;
		case 2:
			for (i = n - 1; i > 0; i--) {
				flag = 0;
				for (j = 1; j <= i; j++) {
					cmpcnt++;
					if (a[j - 1] > a[j]) {
						flag = 1;
						swap (&a[j - 1], &a[j]);
					}
				}
				if (!flag) break;
			}
			break;
		case 3:
			for (i = (n - 1) >> 1; i >= 0; i--) adjust(i, n);
			for (i = n - 1; i > 0; i--) {
				swap(&a[i], &a[0]);
				adjust(0, i);
			}
			break;
		case 4:
			mergeSort(0, n - 1);
			break;
		case 5:
			quickSort(0, n - 1);
	}
	printf("%d", a[0]);
	for (i = 1; i < n; i++) {
		printf(" %d", a[i]);
	}
	printf("\n%d\n", cmpcnt);
	return 0;
}

