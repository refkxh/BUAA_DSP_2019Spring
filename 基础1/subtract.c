#include <stdio.h>
#include <string.h>
char a[100],b[100];
int c[100],d[100],e[100];
int l1=99,l2=99;
int mx (int x,int y) {
	return x>y?x:y;
}
void conv (char a[],int b[]) {
	int len=strlen(a),i=0,j=len-1;
	if (j<0) return;
	for (;i<len;i++,j--) {
		b[i]=a[j]-'0';
	}
}
int cmp () {
	int i=l1;
	if (l1>l2) return 1;
	else if (l1<l2) return 0;
	else {
		for (;i>=0;i--) {
			if (c[i]>d[i]) return 1;
			else if (c[i]<d[i]) return 0;
		}
	}
	return 1;
}
void proc (int c[],int d[]) {
	int i;
	for (i=0;i<mx(l1,l2);i++) {
		e[i]=c[i]-d[i];
		if (e[i]<0) {
			e[i]+=10;
			c[i+1]--;
		}
	}
}
int main () {
	int i;
	scanf ("%s%s",a,b);
	conv (a,c);
	conv (b,d);
	while (l1>0&&c[l1-1]==0) l1--;
	while (l2>0&&d[l2-1]==0) l2--;
	if (cmp ()) proc (c,d);
	else {
		putchar('-');
		proc (d,c);
	}
	i=99;
	while (i>0&&e[i]==0) i--;
	while (i>=0) {
		printf ("%d",e[i]);
		i--;
	}
	putchar ('\n');
	return 0;
}


