#include <iostream>
#include <unordered_map>
using namespace std;

// P3367 ��ģ�塿���鼯
// https://www.luogu.com.cn/problem/P3367

// �����ϲ�
// �飺����
// ��������

class UFSetSimple {
public:
    void Init(int maxId);
    int Find(int id);
    bool Union(int id1, int id2);
private:
    unordered_map<int, int> m_set;    // m_set[x] ������ x ���ڵļ��ϱ��
};

void UFSetSimple::Init(int maxId) {
    m_set.clear();
    for (int i = 1; i <= maxId; ++i) {
        m_set[i] = i;
    }
}

int UFSetSimple::Find(int id) {
    return m_set[id];
}

bool UFSetSimple::Union(int id1, int id2) {
    int s1 = Find(id1), s2 = Find(id2);
    if (s1 == s2) {
        return false;   // �ϲ�ʧ��
    }
    int n = m_set.size();
    for (int i = 1; i <= n; ++i) {
        if (m_set[i] == s1) {
            m_set[i] = s2;
        }
    }
    return true;    // �ϲ��ɹ�
}



int main() {
    int n, m;
    UFSetSimple uf;
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


