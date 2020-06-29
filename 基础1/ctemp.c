#include <stdio.h>
int sel[20],prt[20];
int n;
void perm (int cur) {
	int i,j;
	if (cur==n) {
		for (j=0;j<n;j++) {
			if (j>0) putchar (' ');
			printf ("%d",prt[j]);
		}
		putchar ('\n');
		return;
	}
	for (i=1;i<=n;i++) {
		if (sel[i]==0) {
			sel[i]=1;
			prt[cur]=i;
			perm (cur+1);
			sel[i]=0;
		}
	}
}
int main () {
	scanf ("%d",&n);
	perm (0);
	return 0;
}


