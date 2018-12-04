/*
https://informatics.mccme.ru/mod/statements/view.php?id=1974#1
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

const int N = (int)1e5 + 7;
const int inf = (int)1e9 + 7;

struct item {
	int x, y;
	item *l, *r, *pr;
	int id;
	item(int _x, int _y, int _id) {
		x = _x; y = _y; id = _id;
		l = NULL; r = NULL; pr = NULL;
	}
};

typedef item * pitem;      

void split(pitem t, int x, pitem &l, pitem &r) {
	if (t == NULL) {
		l = r = NULL;
	} else if (t -> x > x) {
		split(t -> l, x, l, t -> l);
		r = t;
	} else {
		split(t -> r, x, t -> r, r);
		l = t;
	}
}

void insert(pitem &t, pitem a) {
	if (t == NULL) {
		t = a;
	} else if (a -> y > t -> y) {
		split(t, a -> x, a -> l, a -> r);
		t = a;
	} else {
		if (t -> x < a -> x) {
			insert(t -> r, a);
		} else {
			insert(t -> l, a);
		}
	}
}

pair < int, pii > ar[N];

void go(pitem &t) {	
	if (t -> l != NULL) {
		go(t -> l);
		ar[t -> l -> id].fr = t -> id;
		ar[t -> id].sc.fr = t -> l -> id;
	} else {
		ar[t -> id].sc.fr = 0;
	} 
	if (t -> r != NULL) {
		go(t -> r);
		ar[t -> r -> id].fr = t -> id;
		ar[t -> id].sc.sc = t -> r -> id;
	} else {
		ar[t -> id].sc.sc = 0;
	}
}

pitem tree, aa, last, cur;

int n;
int a, b;
pair < int, pii > arr[N];

void print() {
	while (last -> pr != NULL) last = last -> pr;
	go(last);
	puts("YES");
	for (int i = 1; i <= n; i++) {
		printf("%d %d %d\n", ar[i].fr, ar[i].sc.fr, ar[i].sc.sc);
	}
	exit(0);
}

main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif	          
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a, &b);
		b = -b;
		arr[i] = mk(a, mk(b, i));
	}	
	sort(arr + 1, arr + n + 1);
	tree = new item(arr[1].fr, arr[1].sc.fr, arr[1].sc.sc);
	last = tree;
	for (int i = 2; i <= n; i++) {
		if (last -> y > arr[i].sc.fr) {
			last -> r = new item(arr[i].fr, arr[i].sc.fr, arr[i].sc.sc);
			last -> r -> pr = last;
			last = last -> r;
			// printf("*** %d\n", i);
		} else {
			cur = last;
			while (cur -> pr != NULL && cur -> y <= arr[i].sc.fr) {
				cur = cur -> pr;
			}
			if (cur -> y <= arr[i].sc.fr) {
				// cout << i << endl;
				last = new item(arr[i].fr, arr[i].sc.fr, arr[i].sc.sc);
				cur -> pr = last;
				last -> l = cur;
			} else {
				// cout << "###" << i << endl;
				last = new item(arr[i].fr, arr[i].sc.fr, arr[i].sc.sc);
				last -> l = cur -> r;
				last -> pr = cur;
				cur -> r = last; 				
			}
		}
	}
	print();
}
