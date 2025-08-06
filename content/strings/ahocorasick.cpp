namespace aho {
int go(int v, char ch);
const int K = 26;  // tamanho do alfabeto
struct trie {
  char me;             // char correspondente ao no atual
  int go[K];           // proximo vertice que eu devo ir estando em um estado (v, c)
  int down[K];         // proximo vertice da trie
  int is_leaf = 0;     // se o vertice atual da trie eh uma folha (fim de uma ou mais strings)
  int parent = -1;     // no ancestral do no atual
  int link = -1;       // link de sufixo do no atual (outro no com o maior matching de sufixo)
  int exit_link = -1;  // folha mais proxima que pode ser alcancada a partir de v usando links de sufixo
  trie(int p = -1, char ch = '$') : parent(p), me(ch) {
    fill(begin(go), end(go), -1);
    fill(begin(down), end(down), -1);
  }
};
vector<trie> ac;
void init()  // criar a raiz da trie
{
  ac.resize(1);
}
void add_string(string s)  // adicionar string na trie
{
  int v = 0;
  for (auto const &ch : s) {
    int c = ch - 'a';
    if (ac[v].down[c] == -1) {
      ac[v].down[c] = ac.size();
      ac.emplace_back(v, ch);
    }
    v = ac[v].down[c];
  }
  ac[v].is_leaf++;
}
int get_link(int v)  // pegar o suffix link saindo de v
{
  if (ac[v].link == -1) ac[v].link = (!v || !ac[v].parent) ? 0 : go(get_link(ac[v].parent), ac[v].me);
  return ac[v].link;
}
int go(int v, char ch)  // proximo estado saindo do estado(v, ch)
{
  int c = ch - 'a';
  if (ac[v].go[c] == -1) {
    if (ac[v].down[c] != -1)
      ac[v].go[c] = ac[v].down[c];
    else
      ac[v].go[c] = (!v) ? 0 : go(get_link(v), ch);
  }
  return ac[v].go[c];
}
int get_exit_link(int v)  // suffix link mais proximo de v que seja uma folha
{
  if (ac[v].exit_link == -1) {
    int curr = get_link(v);
    if (!v || !curr)
      ac[v].exit_link = 0;
    else if (ac[curr].is_leaf)
      ac[v].exit_link = curr;
    else
      ac[v].exit_link = get_exit_link(curr);
  }
  return ac[v].exit_link;
}
int query(string s)  // query O(n + ans)
{
  int ans = 0, curr = 0, at;
  for (auto const &i : s) {
    curr = go(curr, i);
    ans += ac[curr].is_leaf;
    at = get_exit_link(curr);
    while (at) {
      ans += ac[at].is_leaf;
      at = get_exit_link(at);
    }
  }
  return ans;
}
}  // namespace aho