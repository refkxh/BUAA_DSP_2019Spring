#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ch[60];
typedef struct book {
	char nam[60], author[30], pub[40], dt[20];
} book;
book books[505];
int cmp(const void *p1, const void *p2) {
	const book *pt1 = p1, *pt2 = p2;
	return strcmp(pt1->nam, pt2->nam);
}
int main() {
	int op, num = 0, i;
	FILE *in = fopen("books.txt", "r"), *out = fopen("ordered.txt", "w");
	while (fscanf(in, "%s%s%s%s", books[num].nam, books[num].author, books[num].pub, books[num].dt) != EOF) num++;
	qsort(books, num, sizeof(book), cmp);
	while (1) {
		scanf("%d", &op);
		switch (op) {
		case 0:
			for (i = 0; i < num; i++) {
				fprintf(out, "%-50s%-20s%-30s%-10s\n", books[i].nam, books[i].author, books[i].pub, books[i].dt);
			}
			fclose(in);
			fclose(out);
			return 0;
		case 1:
			scanf("%s%s%s%s", books[num].nam, books[num].author, books[num].pub, books[num].dt);
			num++;
			qsort(books, num, sizeof(book), cmp);
			break;
		case 2:
			scanf("%s", ch);
			for (i = 0; i < num; i++) {
				if (strstr(books[i].nam, ch)) printf("%-50s%-20s%-30s%-10s\n", books[i].nam, books[i].author, books[i].pub, books[i].dt);
			}
			break;
		case 3:
			scanf("%s", ch);
			for (i = 0; i < num; i++) {
				if (strstr(books[i].nam, ch)) {
					books[i] = books[--num];
					i--;
				}
			}
			qsort(books, num, sizeof(book), cmp);
		}
	}
}


