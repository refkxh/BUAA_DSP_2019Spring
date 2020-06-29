#include <stdio.h>
#include <ctype.h>
int nums[1107];
char ops[1107];
int main() {
	int numcap = 0, opcap = 0, tmp = 0, flag = 0;
	char ch, op;
	while (1) {
		ch = getchar();
		if (ch == '=') {
			if (flag) nums[numcap++] = tmp;
			while (opcap) {
				ch = ops[--opcap];
				if (ch == '+') nums[numcap - 2] += nums[numcap - 1];
				else if (ch == '-') nums[numcap - 2] -= nums[numcap - 1];
				else if (ch == '*') nums[numcap - 2] *= nums[numcap - 1];
				else if (ch == '/') nums[numcap - 2] /= nums[numcap - 1];
				else nums[numcap - 2] %= nums[numcap - 1];
				numcap--;
			}
			printf("%d\n", nums[0]);
			return 0;
		}
		else if (isdigit(ch)) {
			flag = 1;
			tmp = tmp * 10 + ch - '0';
		}
		else if (ch == '+' || ch == '-') {
			if (flag) {
				flag = 0;
				nums[numcap++] = tmp;
				tmp = 0;
			}
			while (opcap && ops[opcap - 1] != '(') {
				op = ops[--opcap];
				if (op == '+') nums[numcap - 2] += nums[numcap - 1];
				else if (op == '-') nums[numcap - 2] -= nums[numcap - 1];
				else if (op == '*') nums[numcap - 2] *= nums[numcap - 1];
				else if (op == '/') nums[numcap - 2] /= nums[numcap - 1];
				else nums[numcap - 2] %= nums[numcap - 1];
				numcap--;
			}
			ops[opcap++] = ch;
		}
		else if (ch == '(') {
			if (flag) {
				flag = 0;
				nums[numcap++] = tmp;
				tmp = 0;
			}
			ops[opcap++] = ch;
		}
		else if (ch == ')') {
			if (flag) {
				flag = 0;
				nums[numcap++] = tmp;
				tmp = 0;
			}
			while (ops[opcap - 1] != '(') {
				ch = ops[--opcap];
				if (ch == '+') nums[numcap - 2] += nums[numcap - 1];
				else if (ch == '-') nums[numcap - 2] -= nums[numcap - 1];
				else if (ch == '*') nums[numcap - 2] *= nums[numcap - 1];
				else if (ch == '/') nums[numcap - 2] /= nums[numcap - 1];
				else nums[numcap - 2] %= nums[numcap - 1];
				numcap--;
			}
			opcap--;
		}
		else if (ch == '*' || ch == '/' || ch == '%'){
			if (flag) {
				flag = 0;
				nums[numcap++] = tmp;
				tmp = 0;
			}
			while (opcap && ops[opcap - 1] != '(' && ops[opcap - 1] != '+' && ops[opcap - 1] != '-') {
				op = ops[--opcap];
				if (op == '*') nums[numcap - 2] *= nums[numcap - 1];
				else if (op == '/') nums[numcap - 2] /= nums[numcap - 1];
				else nums[numcap - 2] %= nums[numcap - 1];
				numcap--;
			}
			ops[opcap++] = ch;
		}
	}
}

