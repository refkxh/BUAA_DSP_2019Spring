#include <stdio.h>
#include <string.h>
#include <ctype.h>
char s[1000000];
int main () {
	int i,len,j;
	scanf ("%s",s);
	len=strlen (s);
	for (i=0;i<len;i++) {
		if (s[i]!='-') putchar (s[i]);
		else {
			if (((islower(s[i-1])&&islower(s[i+1]))||(isupper(s[i-1])&&isupper(s[i+1]))||(isdigit(s[i-1])&&isdigit(s[i+1])))&&s[i-1]<s[i+1]){
				for (j=1;j+s[i-1]<s[i+1];j++) {
					putchar (j+s[i-1]);
				}
			} else putchar (s[i]);
		}
	}
	printf ("\n");
	return 0;
}


