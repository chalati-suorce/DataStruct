#include <iostream>
#include <stack>
using namespace std;

/* ����ջģ�� */
#define maxn 100001
#define inf 2000000000

template<typename T>
bool cmp(T a, T b) {
    return a >= b;
}

// ans[i] ����� i �����ң��ҵ��ĵ�һ�� �������� ���±�
template<typename T>
void findFirstMeetOnLeft(int n, T h[], int ans[]) {
    stack<int> stk;
    h[0] = inf;
    stk.push(0);
    for (int i = 1; i <= n; ++i) {
        while (!cmp(h[stk.top()], h[i])) {
            stk.pop();
        }
        ans[i] = stk.top();
        stk.push(i);
    }
}

template<typename T>
void reverseArray(int n, T arr[]) {
    for (int i = 1; i <= n / 2; ++i) {
        T tmp = arr[i];
        arr[i] = arr[n + 1 - i];
        arr[n + 1 - i] = tmp;
    }
}

/* ����ջģ�� */

int h[maxn], ans[maxn];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> h[i];
    }
    findFirstMeetOnLeft(n, h, ans);
    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        // ans[i], ans[i]+1, ans[i]+2, ..., i-1, i
        // (i-1) - (ans[i]+1) + 1 = i - ans[i] - 1
        ret += i - ans[i] - 1;
    }
    cout << ret << endl;
    return 0;
}
