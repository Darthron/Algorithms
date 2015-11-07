#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

int N;
long long x1, x2;
int v1[1000005], v2[1000005];
pair<int, long long> p1[100005];
pair<int, long long> p2[100005];

bool cmp1(pair<int, long long> a, pair<int, long long> b)
{
    if (a.second < b.second)
        return true;
    else if (a. second > b.second)
        return false;
    else
        return v2[a.first] < v2[b.first];
}

bool cmp2(pair<int, long long> a, pair<int, long long> b)
{
    if (a.second < b.second)
        return true;
    else if (a. second > b.second)
        return false;
    else
        return v1[a.first] < v1[b.first];
}

int main()
{
    int i;
    long long a, b;

    cin >> N;
    cin >> x1 >> x2;
    for (i = 0; i < N; i += 1)
    {
        cin >> a;
        cin >> b;
        p1[i].first = i;
        p1[i].second = a * x1 + b;
        p2[i].second = a * x2 + b;
        p2[i].first = i;
        v1[i] = p1[i].second;
        v2[i] = p2[i].second;
    }
    sort(p1, p1 + N, cmp1);
    sort(p2, p2 + N, cmp2);
    for (i = 0; i < N; i += 1)
        if (p1[i].first != p2[i].first)
        {
            cout << "YES";
            return 0;
        }
    cout << "NO";
    return 0;
}
