#include <stdio.h>
#include <string.h>
#include <ctype.h>
char s1[2000],s2[2000],tmp[2000];
int main () {
	int len,pos=0,i,ch;
	FILE *in=fopen ("filein.txt","r"),*out=fopen ("fileout.txt","w");
	scanf ("%s%s",s1,s2);
	len=strlen (s1);
	for (i=0;i<len;i++) {
		s1[i]=tolower(s1[i]);
	}
	while ((ch=fgetc(in))!=EOF) {
		if (tolower(ch)==s1[pos]) {
			tmp[pos++]=ch;
			if (pos==len) {
				fprintf (out,"%s",s2);
				pos=0;
			}
		} else {
			for (i=0;i<pos;i++) {
				fputc (tmp[i],out);
			}
			pos=0;
			fputc (ch,out);
		}
	}
	for (i=0;i<pos;i++) {
		fputc (tmp[i],out);
	}
	fclose (in);
	fclose (out);
	return 0;
}



