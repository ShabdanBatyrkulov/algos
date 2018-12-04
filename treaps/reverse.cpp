/*
https://informatics.mccme.ru/mod/statements/view3.php?id=1974&chapterid=111240#1
*/

#include <bits/stdc++.h>

using namespace std;

#define random (rand() ^ (rand() << 15))
#define pitem item *
#define ok puts("ok");

const int N = (int)1e5 + 7;
const int inf = (int)1e9 + 7;

int n, m;

struct item {
	int x, y, cnt, mn, rev;
	item *l, *r;
	item(){
		l = r = NULL;
	}
	item(int _x) {
		y = rand();
		x = _x;
		cnt = 1;
		l = r = NULL;
		mn = _x;
		rev = 0;
	}
};

int getsz(pitem &t) {
	if (t != NULL)
		return t -> cnt;
	return 0;
}

int getmn(pitem &t) {
	if (t != NULL)
		return t -> mn;
	return inf;	
}

void push(pitem &t) {
	if (t && t -> rev) {
		swap(t -> l, t -> r);
		if (t -> l)
			t -> l -> rev ^= 1;
		if (t -> r)
			t -> r -> rev ^= 1;
		t -> rev = 0;	
	}
}

void updsz(pitem &v) {
	if (v != NULL) {
		v -> cnt = getsz(v -> l) + getsz(v -> r) + 1;
		v -> mn = min(v -> x, min(getmn(v -> l), getmn(v -> r)));
	}
}
void split(pitem t, int key, pitem &l1, pitem &r1, int add = 0) {
	push(t);
	if (t == NULL) {
		l1 = r1 = NULL;
		return ;
	} 
	int ky = getsz(t -> l) + 1 + add;
	if (key > ky) {
		split(t -> r, key, t -> r, r1, ky);
		l1 = t; 
	} else {
		split(t -> l, key, l1, t -> l, add);
		r1 = t;
	}
	updsz(t);
}

void merge(pitem &t, pitem l, pitem r) {
	push(l); push(r);
	if (!l || !r) {
		t = (l) ? l : r;
	} else if (l -> y > r -> y) {
		merge(l -> r, l -> r, r);
		t = l;
	} else {
		merge(r -> l, l, r -> l);
		t = r;
	}
	updsz(t);
}

void insert(pitem &t, pitem nw, int key, int add = 0) {
	pitem a;
	pitem b;
	split(t, key, a, b);
	merge(t, a, nw);
	merge(t, t, b);
}

void check(pitem t) {
	if (t -> l) {
		check(t -> l);
	}
	cout << t -> x << ' ';
	if (t -> r) {
		check(t -> r);
	}
}

int getmin(pitem &t, int l, int r) {
	pitem a;
	pitem b;  
	split(t, l, t, a);
	split(a, r - l + 2, a, b);
	int ret = getmn(a);
	merge(t, t, a);
	merge(t, t, b);
	return ret;
}

void reverse(pitem &t, int l, int r) {
	pitem a;
	pitem b;
	split(t, l, t, a);
	split(a, r - l + 2, a, b);
	a -> rev ^= 1;
	merge(t, t, a);
	merge(t, t, b);
}

main() {                       
	srand(time(0));      
	int q;
	scanf("%d %d", &n, &q);
	pitem root = NULL;	   
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		insert(root, new item(x), i);
	}
	while (q--) {
		int tp;
		scanf("%d", &tp);
		int l, r;
		scanf("%d %d", &l, &r);
		if (tp == 1) {
			reverse(root, l, r);
		} else {
			printf("%d\n", getmin(root, l, r));
		}
	}
}
