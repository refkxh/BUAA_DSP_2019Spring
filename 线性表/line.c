#include <stdio.h>
#include <stdlib.h>
typedef struct line {
	int x1,y1,x2,y2,num;
} line; 
line lines[105];
int cmp (const void *p1,const void *p2) {
	const line *pt1=p1, *pt2=p2;
	return pt2->num-pt1->num;
}
int main () {
	int n,i,j,tx1,ty1,tx2,ty2,cnt=0,flag=1;
	scanf ("%d",&n);
	for (i=0;i<n;i++) {
		scanf ("%d%d%d%d",&tx1,&ty1,&tx2,&ty2);
		for (j=0;j<cnt;j++) {
			if (lines[j].x2==tx1&&lines[j].y2==ty1) {
				lines[j].num++;
				lines[j].x2=tx2;
				lines[j].y2=ty2;
				break;
			} else if (lines[j].x1==tx2&&lines[j].y1==ty2) {
				lines[j].num++;
				lines[j].x1=tx1;
				lines[j].y1=ty1;
				break;
			}
		}
		if (j==cnt) {
			lines[cnt].x1=tx1;
			lines[cnt].x2=tx2;
			lines[cnt].y1=ty1;
			lines[cnt].y2=ty2;
			lines[cnt].num=1;
			cnt++;
		}
	}
	while (flag) {
		flag=0;
		for (i=0;i<cnt-1;i++) {
			for (j=i+1;j<cnt;j++) {
				if (lines[i].x2==lines[j].x1&&lines[i].y2==lines[j].y1) {
					lines[i].x2=lines[j].x2;
					lines[i].y2=lines[j].y2;
					lines[i].num+=lines[j].num;
					lines[j]=lines[--cnt];
					j--;
					flag=1;
				} else if (lines[i].x1==lines[j].x2&&lines[i].y1==lines[j].y2) {
					lines[i].x1=lines[j].x1;
					lines[i].y1=lines[j].y1;
					lines[i].num+=lines[j].num;
					lines[j]=lines[--cnt];
					j--;
					flag=1;
				}
			}
		}
	}
	qsort (lines,cnt,sizeof(line),cmp);
	printf ("%d %d %d\n",lines[0].num,lines[0].x1,lines[0].y1);
	return 0;
}


