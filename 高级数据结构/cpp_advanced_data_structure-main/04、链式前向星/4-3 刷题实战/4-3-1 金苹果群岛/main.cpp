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

    int m_count;
    vector<int> m_colors;         // m_colors[i] �������ÿ�����챻Ⱦɫ�����ɫֵ��һ��ʼû��Ⱦɫ��ʱ����-1

    void dfs(int u);             // �� u �����������к� u ֱ�ӻ��߼�������ĵ������Ⱦɫ
public:
    Graph(int n);
    void addEdge(int from, int to, T weight);
    void printEdges();
    int countConnectedBlock();  // ���������������ͳ��һ��ͼ�У���ͨ�����ĸ���
};

template<class T>
void Graph<T>::dfs(int u) {
    if (m_colors[u] != -1) {
        return;
    }
    m_colors[u] = m_count;
    for (int e = m_head[u]; e != -1; e = m_edges[e].next) {
        dfs(m_edges[e].to);
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
int Graph<T>::countConnectedBlock() {
    int n = (int)m_head.size();
    m_count = 0;
    m_colors.resize(n, -1);
    for (int i = 0; i < n; ++i) {
        if (m_colors[i] == -1) {
            dfs(i);
            m_count++;
        }
    }
    return m_count;
}


int main() {
    int n, m;
    cin >> n >> m;
    Graph <int> g(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g.addEdge(a, b, 0);
        g.addEdge(b, a, 0);
    }
    cout << g.countConnectedBlock() - 1 << endl;

    return 0;
}

