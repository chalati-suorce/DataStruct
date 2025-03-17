#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

template<typename T, typename Compare>
class SparseTable {
private:
    vector<T> m_org;
    vector< vector<int> > m_st;
    Compare m_cmp;
    void init();
public:
    SparseTable(const vector<T>& arr);
    int Query(int l, int r);
};

template<typename T, typename Compare>
void SparseTable<T, Compare>::init() {
    int n = (int)m_org.size();
    // log2(n)+1,  n
    int log2n = (int)log2(n) + 1;
    m_st.assign(log2n, vector<int>(n));
    // st[j][i] ��ʾ���� [i, i + 2^j-1 ] ��������е���ֵ�����ڵ��±꣩
    // st[0][i] ��ʾ���� [i, i] ��������е���ֵ�����ڵ��±꣩���Ǿ��� i
    for (int i = 0; i < n; ++i) {
        m_st[0][i] = i;
    }

    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = 0; i + (1 << j) - 1 < n; ++i) {
            // [i, i+(1<<j)-1]
            /*
                1��st[j][i] �����䳤���� 2^j
                2�����������������Ϊ 2^(j-1) ������
                   2.1 һ�������� [i, i + 2^(j-1) - 1]           =>  st[j-1][i]
                   2.2 һ�������� [i + 2^(j-1), i + 2^j - 1]     =>  st[j-1][i + (1<<(j-1))]
            */
            int idx1 = m_st[j - 1][i];
            int idx2 = m_st[j - 1][i + (1 << (j - 1))];
            m_st[j][i] = m_cmp(m_org[idx1], m_org[idx2]) ? idx1 : idx2;
        }
    }

}

template<typename T, typename Compare>
SparseTable<T, Compare>::SparseTable(const vector<T>& arr) {
    int n = (int)arr.size();
    m_org.assign(arr.begin(), arr.end());
    init();
}

/*
1������ [l, r] ������䣬���Բ�ֳ��������ȷֱ�Ϊ 2^k �����䣺
    һ���������� l ��Ϊ��ʼ�ģ� [l, x]
    һ���������� r ��Ϊ��β�ģ� [y, r]
    ���ң�����������Ĳ����� [l, r]�� ������Ҫ���� x+1 >= y
2���� l ��Ϊ��ʼ������ĳ���Ϊ 2 �� k ��
        ����ʾ��������� [l, l + 2^k - 1]    => x = l + 2^k - 1
   �� r ��Ϊ��β������ĳ���Ϊ 2 �� k ��
        ����ʾ��������� [r - 2^k + 1, r]    => y = r - 2^k + 1
3��l + 2^k - 1 + 1 >= r - 2^k + 1
    ���     2^(k+1)  >= r - l + 1
    ȡ������     k      >= log2(r - l + 1) - 1
    ���� k ��ֵ��Ϊ log2(r - l + 1) ȡ���� �ټ�һ
*/
template<typename T, typename Compare>
int SparseTable<T, Compare>::Query(int l, int r) {
    if (l == r) {
        return l;
    }
    int k = (int)ceil(log2(r - l + 1)) - 1;
    int idx1 = m_st[k][l];
    int idx2 = m_st[k][r - (1 << k) + 1];
    return m_cmp(m_org[idx1], m_org[idx2]) ? idx1 : idx2;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch>'9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - 48; ch = getchar(); }
    return x * f;
}

int main() {
    int n, m;
    n = read();
    m = read();
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = read();
    }
    SparseTable<int, std::less<int> > stl(arr);
    SparseTable<int, std::greater<int> > stg(arr);
    long long minsum = 0, maxsum = 0;
    while (m--) {
        int l = read();
        int r = read();
        --l, --r;
        minsum += arr[stl.Query(l, r)];
        maxsum += arr[stg.Query(l, r)];
    }
    cout << minsum << ' ' << maxsum << endl;

    return 0;
}


