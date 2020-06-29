#include <stdio.h>
#include <string.h>
char s[507], st[500], brc[500], line[500];
int cap = 0, brcs = 0;
int main() {
	FILE *in = fopen("example.c", "r");
	int len, i, neg = 0, ch = 0, str = 0, curl = 0;
	while (fgets(s, 205, in) != NULL) {
		len = strlen(s);
		curl++;
		for (i = 0; i < len; i++) {
			if (s[i] == '/' && s[i + 1] == '/' && !str && !neg) break;
			else if (s[i] == '/' && s[i + 1] == '*' && !str) {
				neg = 1;
				i++;
			}
			else if (s[i] == '*' && s[i + 1] == '/' && !str) {
				neg = 0;
				i++;
			}
			else if (s[i] == '\'' && !neg && !str) ch = !ch;
			else if (s[i] == '\"' && !neg && !ch) str = !str;
			else if (s[i] == '(' && !neg && !ch && !str) {
				line[cap] = curl;
				st[cap++] = s[i];
				brc[brcs++] = s[i];
			}
			else if (s[i] == '{' && !neg && !ch && !str) {
				if (cap && st[cap - 1] == '(') {
					printf("without maching \'%c\' at line %d\n", st[cap - 1], line[cap - 1]);
					fclose(in);
					return 0;
				}
				else {
					line[cap] = curl;
					st[cap++] = s[i];
					brc[brcs++] = s[i];
				}
			}
			else if (s[i] == ')' && !neg && !ch && !str) {
				if ((cap && st[cap - 1] != '(') || !cap) {
					printf("without maching \'%c\' at line %d\n", s[i], curl);
					fclose(in);
					return 0;
				}
				else {
					brc[brcs++] = s[i];
					cap--; 
				}
			}
			else if (s[i] == '}' && !neg && !ch && !str) {
				if ((cap && st[cap - 1] != '{') || !cap) {
					printf("without maching \'%c\' at line %d\n", s[i], curl);
					fclose(in);
					return 0;
				}
				else {
					brc[brcs++] = s[i];
					cap--; 
				}
			}
		}
	}
	if (cap) printf("without maching \'%c\' at line %d\n", st[cap - 1], line[cap - 1]);
	else {
		for (i = 0; i < brcs; i++) {
			putchar(brc[i]);
		}
		putchar('\n');
	}
	fclose(in);
	return 0;
}

