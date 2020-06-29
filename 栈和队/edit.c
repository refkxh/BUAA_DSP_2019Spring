#include <stdio.h>
#include <string.h>
char s[607], tmps[607];
int op[1107], pos[1107];
char str[1107][607];
int main() {
	int n, i, tmp;
	scanf("%[^\n]", s);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d%d%s", &op[i], &pos[i], str[i]);
	}
	while (1) {
		scanf("%d", &tmp);
		if (tmp == -1) {
			printf("%s", s);
			return 0;
		}
		else if (tmp == 1) {
			op[n] = tmp;
			scanf("%d%s", &pos[n], str[n]);
			strcpy(tmps, s + pos[n]);
			strcpy(s + pos[n], str[n]);
			strcat(s, tmps);
			n++;
		}
		else if (tmp == 2) {
			op[n] = tmp;
			scanf("%d%d", &pos[n], &tmp);
			strncpy(str[n], s + pos[n], tmp);
			for (i = pos[n]; s[i + strlen(str[n])] != '\0'; i++) {
				s[i] = s[i + strlen(str[n])];
			}
			s[i] = '\0';
			n++;
		}
		else {
			if (!n) continue;
			n--;
			if (op[n] == 1) {
				for (i = pos[n]; s[i + strlen(str[n])] != '\0'; i++) {
					s[i] = s[i + strlen(str[n])];
				}
				s[i] = '\0';
			}
			else {
				strcpy(tmps, s + pos[n]);
				strcpy(s + pos[n], str[n]);
				strcat(s, tmps);
			}
		}
	}
}

