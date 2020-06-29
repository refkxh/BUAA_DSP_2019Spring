## 小型图书管理系统

------

### 问题描述

> 用C开发一个小型图书管理系统。系统中包含的图书信息有：书名、作者、出版社、出版日期等。首先，图书管理系统对已有的书（原始书库，存放在一个文本文件中）按**书名字典序进行（排序）**摆放（即将原始无序的图书信息文件生成一个有序的文件，即新书库），以便查找。该管理系统可以对新书库中图书条目进行如下操作：
>
> 1. 录入。新增书录入到书库中（即从输入中读入一条图书信息插入到已排序好的图书文件相关位置处）
> 2. 查找。按书名或书名中关键字信息在书库中查找相关图书信息，若有多本书，按字典序输出。
> 3. 删除。输入书名或书名中关键字信息，从书库中查找到相关书并将其删除，并更新书库。

### 输入格式

原始的图书信息（原始书库）保存在当前目录下的books.txt中。

用户操作从控制台读入，首先输入操作功能序号（1代表录入操作，2代表查找操作，3代表删除操作，0代表将已更新的图书信息保存到书库中并退出程序），然后在下一行输入相应的操作信息（录入操作后要输入一条图书信息，查找和删除操作后只要输入书名或书名中部分信息）。程序支行过程中可以进行多次操作，直到退出（输入操作0）程序。

要求：

1. 原始文件中的图书信息与录入的图书信息格式相同，**每条图书信息都在一行上，包括**书名（不超过50个字符）、作者（不超过20个字符）、出版社（不超过30个字符）和出版日期（不超过10个字符），只由英文字母和下划线组成，用一个空格分隔。图书信息**总条数不会超过500**。
2. **下划线字符参加排序**。
3. 图书**不会重名**。

### 输出格式

进行录入和删除操作，系统会更新图书信息，但不会在控制台窗口显示任何信息。

进行查找操作后，将在控制台按书名字典序**分行输出**查找到的图书信息，书名占50个字符宽度，作者占20个字符宽度，出版社占30个字符宽度，出版日期占10个字符宽度，都**靠左对齐输出**。

最终按字典排序的图书信息保存在当前目录下的ordered.txt中，**每条图书信息占一行，格式与查找输出的图书信息相同**。

### 解题思路

使用结构数组存储图书信息，利用qsort函数完成排序操作，按照题目要求实现各个操作即可。

### 代码实现

```c
/*	Author: REF
 *	数据结构第2次作业编程题第5题
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char ch[60];

/*定义结构类型来存储图书信息*/
typedef struct book {
	char nam[60], author[30], pub[40], dt[20];
} book;

book books[505];	//存储图书信息的结构数组

/*qsort函数使用的比较函数*/
int cmp(const void *p1, const void *p2) {
	const book *pt1 = p1, *pt2 = p2;
	return strcmp(pt1->nam, pt2->nam);
}

int main() {
	int op, num = 0, i;
	FILE *in = fopen("books.txt", "r"), *out = fopen("ordered.txt", "w");
	while (fscanf(in, "%s%s%s%s", books[num].nam, books[num].author, books[num].pub, books[num].dt) != EOF) num++;	//从文件读入图书信息并计数
	qsort(books, num, sizeof(book), cmp);	//对图书信息进行排序
	while (1) {
		scanf("%d", &op);
        
        /*根据读入的指令完成相应的操作*/
		switch (op) {
        
        /*退出*/
		case 0:
			for (i = 0; i < num; i++) {
				fprintf(out, "%-50s%-20s%-30s%-10s\n", books[i].nam, books[i].author, books[i].pub, books[i].dt);	//将图书信息按指定宽度左对齐输出到文件
			}
			fclose(in);
			fclose(out);
			return 0;
        
        /*录入并排序*/
		case 1:
			scanf("%s%s%s%s", books[num].nam, books[num].author, books[num].pub, books[num].dt);
			num++;
			qsort(books, num, sizeof(book), cmp);
			break;
        
        /*查找*/
		case 2:
			scanf("%s", ch);
			for (i = 0; i < num; i++) {
				if (strstr(books[i].nam, ch)) printf("%-50s%-20s%-30s%-10s\n", books[i].nam, books[i].author, books[i].pub, books[i].dt);
			}
			break;
        
        /*删除（简易）*/
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
```

