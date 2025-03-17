#include <iostream>
#include <deque>
using namespace std;

/* ��������ģ�� */
#define maxn 100001

template<typename T>
bool max(T a, T b) {
    return a <= b;
}

template<typename T>
bool min(T a, T b) {
    return a >= b;
}

// ����һ������Ϊ n ������ 
// ����һ�����䳤�� k
// ������г��Ȳ����� k �����������е� ���ֵ����Сֵ��
template <typename T>
void findIntervalMinMax(int n, T h[], int k, T ans[], bool (*cmp)(T a, T b)) {
    // ans[i] ����ľ����� i ��β�� ����󳤶�Ϊ k ��������������ֵ����Сֵ��
    deque<int> q;
    for (int i = 0; i < n; ++i) {
        while ( !q.empty() && cmp( h[ q.back() ], h[i] )) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.back() - q.front() + 1 > k) {
            q.pop_front();
        }
        // ans[i] ��ʾ�� i ��β���ҳ��Ȳ����� k �������У�Ԫ�ص����ֵ������ֵ��
        ans[i] = h[ q.front() ];
    }
}
/* ��������ģ�� */


int main() {
    int h[] = { 8,7,6,9,11 };
    int ans[10];
    findIntervalMinMax(5, h, 3, ans, max);
    for (int i = 0; i < 5; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    findIntervalMinMax(5, h, 3, ans, min);
    for (int i = 0; i < 5; ++i) {
        cout << ans[i] << ' ';
    }
    cout << endl;

    return 0;
}