template<int N>
struct ACAuto{
	int tr[N][26], fail[N], cnt[N];
	int idx;
	
	void insert(string word){
		int u = 0;
		for (int i = 0; i < word.size(); i ++ ){
			int c = word[i] - 'a';
			if (!tr[u][c]) tr[u][c] = ++ idx;
			u = tr[u][c];
		}
		cnt[u] ++ ;
	}

	void get_fail(){
		queue<int> q;
		
		for (int i = 0; i < 26; i ++ )
			if (tr[0][i]) q.push(tr[0][i]);

		while (q.size()){
			int u = q.front(); q.pop();
			
			for (int i = 0; i < 26; i ++ )
				if (tr[u][i]) 
					fail[tr[u][i]] = tr[fail[u]][i], q.push(tr[u][i]);
				else 
					tr[u][i] = tr[fail[u][i]];
		}
	}
	
	int get_cnt(string s) const{
		int u = 0, res = 0;
		for (int i = 0; i < s.size(); i ++ ){
			int j = u = tr[u][s[i] - 'a'];
			while (j) res += cnt[j], j = fail[j];
		}

		return res;
	}
	
};