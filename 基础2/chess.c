#include<stdio.h>
int st[20][20];
int judge (int r,int c) {
	int n=st[r][c];
	if (c+3<19&&st[r][c+1]==n&&st[r][c+2]==n&&st[r][c+3]==n&&((c-1>=0&&st[r][c-1]==0)||(c+4<19&&st[r][c+4]==0))) return 1;
	if (r+3<19&&st[r+1][c]==n&&st[r+2][c]==n&&st[r+3][c]==n&&((r-1>=0&&st[r-1][c]==0)||(r+4<19&&st[r+4][c]==0))) return 1;
	if (c+3<19&&r+3<19&&st[r+1][c+1]==n&&st[r+2][c+2]==n&&st[r+3][c+3]==n&&((c-1>=0&&r-1>=0&&st[r-1][c-1]==0)||(c+4<19&&r+4<19&&st[r+4][c+4]==0))) return 1;
	if (c-3>=0&&r+3<19&&st[r+1][c-1]==n&&st[r+2][c-2]==n&&st[r+3][c-3]==n&&((c+1<19&&r-1>=0&&st[r-1][c+1]==0)||(c-4>=0&&r+4<19&&st[r+4][c-4]==0))) return 1;
	return 0;
}
int main () {
	int i,j;
	for (i=0;i<19;i++) {
		for (j=0;j<19;j++) {
			scanf ("%d",&st[i][j]);
		}
	}
	for (i=0;i<19;i++) {
		for (j=0;j<19;j++) {
			if (st[i][j]==0) continue;
			if (judge(i,j)) {
				printf ("%d:%d,%d\n",st[i][j],i+1,j+1);
				return 0;
			}
		}
	}
	printf ("No\n");
	return 0;
}


