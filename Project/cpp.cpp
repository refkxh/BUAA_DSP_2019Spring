#include <cstdio>
#include <cstring>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int num = 0;
char tmp[57];

struct word {
	char w[57];
	bool operator < (const word &rhs) const {
		return strcmp(w, rhs.w) < 0;
	}
	word() {
		strcpy(w, tmp);
	}
} tmpw;

struct node {
	char w[57];
	int freq;
	vector<int> p;
	bool operator < (const node &rhs) const {
		if (freq > rhs.freq) return true;
		else if (freq == rhs.freq && strcmp(w, rhs.w) < 0) return true;
		else return false;
	}
	node(char rw[], int pos) {
		strcpy(w, rw);
		p.push_back(pos);
		freq = 1;
	}
};

set<word> dict;
map<word, int> mp;
vector<node> ans;

int readWord(FILE *f) {
	char ch;
	int cnt = 0;
	num = 0;
	while ((ch = getc(f)) != EOF) {
		if (isalpha(ch)) tmp[cnt++] = tolower(ch);
		else {
			num++;
			if (cnt) break;
		}
	}
	tmp[cnt] = '\0';
	return cnt;
}

int main() {
	FILE *dic = fopen("dictionary.txt", "r"), *in = fopen("article.txt", "r"), *out = fopen("misspelling.txt", "w");
	int pos = 0, len;

	while (readWord(dic)) dict.insert(word());

	while (len = readWord(in)) {
		tmpw = word();
		pos += num - 1;
		if (!dict.count(tmpw)) {
			if (mp.count(tmpw)) {
				ans[mp[tmpw]].freq++;
				ans[mp[tmpw]].p.push_back(pos);
			}
			else {
				mp[tmpw] = ans.size();
				ans.push_back(node(tmp, pos));
			}
		}
		pos += len + 1;
	}

	sort(ans.begin(), ans.end());

	int ed = ans.size();
	for (int i = 0; i < ed; i++) {
		fprintf(out, "%s %d", ans[i].w, ans[i].freq);
		for (int j = 0; j < ans[i].freq; j++) {
			fprintf(out, " %d", ans[i].p[j]);
		}
		fprintf(out, "\n");
	}

	fclose(dic);
	fclose(in);
	fclose(out);

	return 0;
}
