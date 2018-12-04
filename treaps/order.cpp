/*
https://informatics.mccme.ru/mod/statements/view3.php?id=1974&chapterid=2791#1
*/

#include <bits/stdc++.h>

using namespace std;

#define random (rand() ^ (rand() << 15))
#define pitem item *

const int N = (int)1e5 + 7;

int n, m;

struct item {
	int x, y, cnt;
	item *l, *r;
	item(){
		l = r = NULL;
	}
	item(int _x) {
		y = rand();
		x = _x;
		cnt = 1;
		l = r = NULL;
	}
};

int getsz(pitem &t) {
	if (t != NULL)
		return t -> cnt;
	return 0;
}

void updsz(pitem &v) {
	if (v != NULL)
		v -> cnt = getsz(v -> l) + getsz(v -> r) + 1;
}
void split(pitem t, int key, pitem &l1, pitem &r1, int add = 0) {
	if (t == NULL) {
		l1 = r1 = NULL;
		return ;
	} 
	int ky = getsz(t -> l) + 1 + add;
	if (key >= ky) {
		split(t -> r, key, t -> r, r1, ky);
		l1 = t; 
	} else {
		split(t -> l, key, l1, t -> l, add);
		r1 = t;
	}
	updsz(t);
}
void insert(pitem &t, pitem nw, int key, int add = 0) {
	if (!t) {
		t = nw;
	} else if (t -> y < nw -> y) {
		split(t, nw -> x, nw -> l, nw -> r);
		t = nw;
	} else {
		int ky = add + getsz(t -> l) + 1;
		if (key >= ky) {
			insert(t -> r, nw, key, ky);
		} else {
			insert(t -> l, nw, key, add);
		}
	}
	updsz(t);
}
void merge(pitem &t, pitem l, pitem r) {
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

void check(pitem t) {
	if (t -> l) {
		check(t -> l);
	}
	cout << t -> x << ' ';
	if (t -> r) {
		check(t -> r);
	}
}

main() {         
	srand(time(0));      
	scanf("%d %d", &n, &m);
	pitem root = new item(1); 
	for (int i = 2; i <= n; i++) {
		insert(root, new item(i), i);
	}
	while (m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		pitem a = new item();
		pitem b = new item();
		pitem c = new item();
		pitem d = new item();
		split(root, l - 1, a, b);
		split(b, r - l + 1, c, d);
		b = new item();
		merge(b, c, a);
		root = new item();
		merge(root, b, d);
		//return 0;
	}        
	check(root);
}
