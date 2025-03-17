#include <iostream>
#include <deque>
using namespace std;

/* ��������ģ�� */
#define maxn 1000001

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
        while (!q.empty() && cmp(h[q.back()], h[i])) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.back() - q.front() + 1 > k) {
            q.pop_front();
        }
        // ans[i] ��ʾ�� i ��β���ҳ��Ȳ����� k �������У�Ԫ�ص����ֵ������ֵ��
        ans[i] = h[q.front()];
    }
}
/* ��������ģ�� */

int h[maxn], G[maxn], F[maxn];

int main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    findIntervalMinMax(n, h, k, G, max);
    findIntervalMinMax(n, h, k, F, min);
    int ret = -1000000000;
    for (int i = 0; i < n; ++i) {
        int v = G[i] - F[i];
        if (v > ret) {
            ret = v;
        }
    }
    cout << ret << endl;
    return 0;
}