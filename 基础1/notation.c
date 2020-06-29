#include <stdio.h>
#include <string.h>
char s[110];
int main () {
	int it1=0,it2=0,tit2,len,flag=0;
	scanf ("%s",s);
	it1=strchr(s,'.')-s;
	while (s[it2]=='0'||s[it2]=='.') it2++;
	tit2=it2;
	len=strlen(s);
	putchar (s[it2++]);
	if (it2<len) putchar ('.');
	while (it2<len) {
		if (s[it2]!='.') putchar (s[it2]);
		else flag=1;
		it2++;
	}
	printf ("e%d\n",it1-tit2-flag);
	return 0; 
}


