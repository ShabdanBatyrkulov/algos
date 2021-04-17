const int inf = (int)1e9 + 7;
struct Dinic {
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
	
	bool bfs() {
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
				if (ed[id].c - ed[id].f > 0 && d[to] == inf) {
					d[to] = d[v] + 1;
					q.push(to);
				}
			}
		}
		return d[t] != inf;
	}
	
	int dfs(int v, int flow = inf) {
		if (v == t || flow == 0) return flow;
		for (int &i = pt[v]; i < gr[v].size(); i++) {
			int id = gr[v][i];
			int to = ed[id].to;
			if (d[v] + 1 == d[to]) {
				int pushed = dfs(to, min(flow, ed[id].c - ed[id].f));
				if (pushed) {
					ed[id].f += pushed;
					ed[id ^ 1].f -= pushed;
					return pushed;
				}
			}
		}
		return 0;
	}
	
	long long getflow() {
		long long flow = 0;
		while (bfs()) {
			for (int i = 0; i < sz; i++) {
				pt[i] = 0;
			}
			int pushed;
			while (pushed = dfs(s)) {
				flow += pushed;
				//cout << "ASD\n";
			}
		}	
		return flow;
	}
};
