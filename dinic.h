struct Dinic {
	const int inf = (int)1e9 + 7;
	int s, t, sz;
	vector < vector <int> > gr;
	vector <int> pt, d;
	Dinic() {
		sz = 0;
	}
	Dinic(int _sz) {
		sz = _sz;
		gr.resize(sz);
		pt.resize(sz);
		d.resize(sz);
	}
	struct edge {
		int v, to, f, c;
		edge() {}
		edge(int _v, int _to, int _flow, int _cap) {
			v = _v;
			to = _to;
			f = _flow;
			c = _cap;
		}
	};
	vector < edge > ed;
	
	void addedge(int a, int b, int c) {
		gr[a].push_back(ed.size());
		ed.push_back(edge(a, b, 0, c));
		gr[b].push_back(ed.size());
		ed.push_back(edge(b, a, c, c));
	}
	
	bool bfs(int lim) {
		for (int i = 0; i < sz; i++) {
			d[i] = inf;
		}
		queue < int > q;
		q.push(s);
		d[s] = 0;
		int v;
		while (!q.empty() && d[t] == inf) {
			v = q.front();
			q.pop();
			for (int id : gr[v]) {
				int to = ed[id].to;
				if (ed[id].c - ed[id].f >= lim && d[to] == inf) {
					d[to] = d[v] + 1;
					q.push(to);
				}
			}
		}
		return d[t] != inf;
	}
	
	bool dfs(int v, int lim) {
		if (v == t) return true;
		for (int &i = pt[v]; i < gr[v].size(); i++) {
			int id = gr[v][i];
			int to = ed[id].to;
			if (d[v] + 1 == d[to] && ed[id].c - ed[id].f >= lim) {
				if (dfs(to, lim)) {
					ed[id].f += lim;
					ed[id ^ 1].f -= lim;
					return true;
				}
			}
		}
		return false;
	}
	
	int getflow() {
		int flow = 0;
		for (int lim = (1 << 30); lim > 0; ) {
			if (!bfs(lim)) {
				lim >>= 1;
				continue;
			}
			for (int i = 0; i < sz; i++) {
				pt[i] = 0;
			}
			while (dfs(s, lim)) {
				flow += lim;
				//cout << "ASD\n";
			}
		}	
		return flow;
	}
};
