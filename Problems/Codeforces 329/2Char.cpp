#include <iostream>
#include <string.h>

using namespace std;

int N;
int chars[27][27];
char words[100][1005];

int main()
{
    int i, j;
    int maxim;
    char c1, c2;
    bool ok;

    cin >> N;
    cin.ignore();
    for (i = 0; i < N; i += 1)
        cin.getline(words[i], 1001);
    for (i = 0; i < N; i += 1)
    {
        int l;
        ok = 1;
        c1 = words[i][0];
        c2 = words[i][0];
        l = strlen(words[i]);
        for (j = 1; j < l; j += 1)
        {
            if (c1 != c2)
            {
                if (words[i][j] != c1 and words[i][j] != c2)
                {
                    ok = 0;
                    break;
                }
            }
            else
                if (words[i][j] != c1)
                    c2 = words[i][j];
        }
        if (ok == 1)
        {
            chars[c1 - 97][c2 - 97] += l;
            if (c1 != c2)
                chars[c2 - 97][c1 - 97] += l;
        }
    }
    maxim = 0;
    for (i = 0; i < 26; i += 1)
    {
        for (j = 0; j < 26; j += 1)
        {
            if (i != j)
                if (maxim < chars[i][j] + chars[i][i] + chars[j][j])
                    maxim = chars[i][j] + chars[i][i] + chars[j][j];
            if (i == j)
                if (maxim < chars[i][i])
                    maxim = chars[i][i];
        }
    }
    cout << maxim;
    return 0;
}
