#include <iostream>
#include <vector>
using namespace std;

/* C++��ʽǰ����ģ�� */

// �ߵ�����ǲ���Ҫ�洢��
// ��Ϊ���������ͬ�ıߣ��ᱻһ��������������
template<typename T>
struct Edge {
    int to;
    T weight;
    int next;
};

template<class T>
class Graph {
private:
    vector< Edge<T> > m_edges;   // m_edges[i] ����ľ��Ǳ��Ϊ i ��������
    vector<int> m_head;          // m_head[i] ��ʾ������i��Ϊ�����Ǹ����������ͷ

    vector<bool>    m_visited;   // m_visited[i] Ϊ true ��ʱ�򣬴�����ʹ��ˣ��������û�б�����
    void dfs(int u, int& ans);   // u����ӵ�ǰ�㿪ʼ���ʣ�ans������ʹ����б�ŵ����ֵ
public:
    Graph(int n);
    void addEdge(int from, int to, T weight);
    void printEdges();
    int caculateColor(int u);    // ����� u �������ܹ����ʵ��������ı��
};

template<class T>
void Graph<T>::dfs(int u, int& ans) {
    if (m_visited[u]) {
        return;
    }
    m_visited[u] = true;
    if (u > ans) {
        ans = u;
    }
    for (int e = m_head[u]; e != -1; e = m_edges[e].next) {
        // (u -> v)
        int v = m_edges[e].to;
        dfs(v, ans);
    }
}

template<class T>
Graph<T>::Graph(int n) {
    m_edges.clear();
    m_head.resize(n, -1);   // m_head ��һ��ֵ��Ϊ-1������
}

template<class T>
void Graph<T>::addEdge(int from, int to, T weight) {
    m_edges.push_back(Edge<T>{to, weight, m_head[from]});
    m_head[from] = (int)m_edges.size() - 1;
}

template<class T>
void Graph<T>::printEdges() {
    int n = m_head.size();
    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int e = m_head[i]; e != -1; e = m_edges[e].next) {
            int v = m_edges[e].to;
            T w = m_edges[e].weight;
            cout << "(" << v << "," << w << ")";
        }
        cout << endl;
    }
}

/* C++��ʽǰ����ģ�� */

template<class T>
int Graph<T>::caculateColor(int u) {
    int n = m_head.size();
    m_visited.resize(n);
    for (int i = 0; i < n; ++i) {
        m_visited[i] = false;
    }
    int ans = u;
    dfs(u, ans);
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    Graph<int> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.addEdge(a, b, 0);
    }
    for (int i = 0; i < n; ++i) {
        cout << g.caculateColor(i) + 1 << " ";
    }
    cout << endl;
    return 0;
}

