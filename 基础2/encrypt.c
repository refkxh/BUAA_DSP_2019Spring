#include <stdio.h>
#include <string.h>
#include <ctype.h>
char s[55],cd[26];
int vis[26];
int main () {
	int cur=0,i,len,ch;
	FILE *in=fopen ("encrypt.txt","r"), *out=fopen ("output.txt","w");
	scanf ("%s",s);
	len=strlen (s);
	for (i=0;i<len;i++) {
		if (!vis[s[i]-'a']) {
			vis[s[i]-'a']=1;
			cd[cur++]=s[i];
		}
	}
	for (i=25;i>=0;i--) {
		if (!vis[i]) cd[cur++]=i+'a';
	}
	while ((ch=fgetc(in))!=EOF) {
		if (isalpha (ch)) fputc (cd[ch-'a'],out);
		else fputc (ch,out);
	}
	fclose (in);
	fclose (out); 
	return 0;
}


