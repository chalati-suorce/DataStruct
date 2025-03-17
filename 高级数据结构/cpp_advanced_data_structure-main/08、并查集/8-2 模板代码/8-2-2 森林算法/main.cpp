#include <iostream>
#include <unordered_map>
using namespace std;

// P3367 ��ģ�塿���鼯
// https://www.luogu.com.cn/problem/P3367

// �����ϲ�
// �飺����
// ��������

class UFSetForest {
public:
    void Init(int maxId);
    int Find(int id);
    bool Union(int id1, int id2);
private:
    unordered_map<int, int> m_far;  // m_far[x]  ������������� x �ĸ������
};

void UFSetForest::Init(int maxId) {
    m_far.clear();
    for (int i = 1; i <= maxId; ++i) {
        m_far[i] = i;
    }
}

int UFSetForest::Find(int id) {
    int p = m_far[id];
    while (p != m_far[p]) {
        p = m_far[p];
    }
    return p;
}

bool UFSetForest::Union(int id1, int id2) {
    int s1 = Find(id1), s2 = Find(id2);
    if (s1 == s2) {
        return false;   // �ϲ�ʧ��
    }
    m_far[s1] = s2;
    return true;    // �ϲ��ɹ�
}

int main() {
    int n, m;
    UFSetForest uf;
    cin >> n >> m;
    uf.Init(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            uf.Union(b, c);
        }
        else {
            if (uf.Find(b) == uf.Find(c)) {
                cout << 'Y' << endl;
            }
            else {
                cout << 'N' << endl;
            }
        }
    }
    return 0;
}


