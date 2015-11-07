#include <fstream>

using namespace std;

const int MAXN = 10000005;

int primes[1001];
int numbers[MAXN];
int minp[1001];
int N, K;

int    get_min()
{
    int minim;

    minim = numbers[minp[0]] * primes[0];
    for (int i = 1; i < K; i += 1)
        if (numbers[minp[i]] * primes[i] < minim)
            minim = numbers[minp[i]] * primes[i];
    for (int i = 0; i < K; i += 1)
        if (numbers[minp[i]] * primes[i] == minim)
            minp[i] += 1;
    return minim;
}

int     main()
{
    int i;
    ifstream mama("primes.in");
    ofstream tata("primes.out");

    mama >> N >> K;
    for (i = 0; i < K; i += 1)
        mama >> primes[i];
    numbers[0] = 1;
    for (i = 1; i <= N; i += 1)
        numbers[i] = get_min();
    for (i = 1; i <= N; i += 1)
        tata << numbers[i] << '\n';
    return 0;
}
