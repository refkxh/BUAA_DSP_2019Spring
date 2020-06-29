#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct it {
	char nam[30],num[20];
} it;
it its[105];
char tnam[30],tnum[20];
int cmp (const void *p1, const void *p2) {
	const it *pt1=p1, *pt2=p2;
	return strcmp (pt1->nam,pt2->nam);
}
int main () {
	int n,i,j,cur=0,id,flag;
	scanf ("%d",&n);
	for (i=0;i<n;i++) {
		scanf ("%s%s",tnam,tnum);
		id=0;
		flag=0;
		for (j=0;j<cur;j++) {
			if (!strncmp (tnam,its[j].nam,strlen(tnam))) {
				if (!strcmp (tnum,its[j].num)) {
					flag=1;
					break;
				} else id++;
			}
		}
		if (flag) continue;
		else {
			strcpy(its[cur].nam,tnam);
			strcpy(its[cur++].num,tnum);
			if (id) sprintf (its[cur-1].nam+strlen(tnam),"_%d",id);
		}
	}
	qsort (its,cur,sizeof(it),cmp);
	for (i=0;i<cur;i++) {
		printf ("%s %s\n",its[i].nam,its[i].num);
	}
	return 0;
}


