#include <iostream>
#include <unordered_map>
using namespace std;

// P3367 ��ģ�塿���鼯
// https://www.luogu.com.cn/problem/P3367

// �����ϲ�
// �飺����
// ��������

class UFSetStar {
public:
    void Init(int maxId);
    int Find(int id);
    bool Union(int id1, int id2);
private:
    unordered_map<int, int> m_far;      // m_far[x]  ������������� x �ĸ������
    unordered_map<int, int>  m_height;  // m_height[x] ������ x Ϊ����������ĸ߶�
};

void UFSetStar::Init(int maxId) {
    m_far.clear();
    m_height.clear();
    for (int i = 1; i <= maxId; ++i) {
        m_far[i] = i;
        m_height[i] = 1;
    }
}

int UFSetStar::Find(int id) {
    int p = m_far[id];
    while (p != m_far[p]) {
        p = m_far[p];
    }
    return p;
}

bool UFSetStar::Union(int id1, int id2) {
    int s1 = Find(id1), s2 = Find(id2);
    if (s1 == s2) {
        return false;   // �ϲ�ʧ��
    }
    if (m_height[s1] < m_height[s2]) {
        m_far[s1] = s2;
    }else if (m_height[s2] < m_height[s1]) {
        m_far[s2] = s1;
    }
    else {
        m_far[s1] = s2;
        m_height[s2]++;
    }
    return true;    // �ϲ��ɹ�
}

int main() {
    int n, m;
    UFSetStar uf;
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


