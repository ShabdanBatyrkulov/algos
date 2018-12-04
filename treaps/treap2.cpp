/*
https://informatics.mccme.ru/mod/statements/view3.php?id=1974&chapterid=2782#1
*/

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define eb emplace_back
#define ll long long
#define pii pair < int, int >
#define fr first
#define sc second
#define mk make_pair
#define sz(s) (int)s.size()
#define all(s) s.begin(), s.end()
#define ok puts("ok");
#define whatis(x) cerr << #x << " = " << x << endl;
#define pause system("pause");

const int N = (int)3e5 + 7;
const int inf = (int)1e9 + 7;

struct item {
	int x, y;
	item *l, *r;
	item(int _x, int _y) {
		x = _x; y = _y;
		l = NULL; r = NULL;
	}
};

typedef item * pitem;

void split(pitem t, int x, pitem &l, pitem &r) {
	if (t == NULL) 
		l = r = NULL;
	else if (t -> x > x) 
		split(t -> l, x, l, t -> l), r = t;
	else 
		split(t -> r, x, t -> r, r), l = t;
}

void insertt(pitem &t, pitem a) {
	if (t == NULL) {
		t = a;
	} else if (a -> y > t -> y) {
		split(t, a -> x, a -> l, a -> r);
		t = a;
	} else {
		if (t -> x < a -> x) {
			insertt(t -> r, a);
		} else {
			insertt(t -> l, a);
		}
	}
}

pitem tree = NULL, add;

int next(int x) {
	int ret = -1;
	pitem cur = tree;
	while (cur != NULL) {
		if (cur -> x < x) {
			cur = cur -> r;
		} else {
			if (ret == -1 || cur -> x < ret)
				ret = cur -> x;
			cur = cur -> l;
		}
	}
	return ret;
}

int n;

main() {
	srand(time(0));
	scanf("%d", &n);
	char cx;                                                                                          
	int x, last;
	last = 0;
	for (int i = 1; i <= n; i++) {
		scanf("\n%c %d", &cx, &x);     
		if (cx == '+') {
			int sec = rand();
			add = new item((x + last) % (int)1e9, sec);
			insertt(tree, add);
			last = 0;
		} else {
			last = next(x);
			printf("%d\n", last);
		}
	}
}
