#include <iostream>
#include <utility>
#include <math.h>

void panic();

std::pair<unsigned,unsigned> findpq(unsigned);
bool isPrime(unsigned);
int* gcd(unsigned,unsigned);
unsigned deCrypt(unsigned, unsigned, unsigned);
char charize(int);

int main()
{
    unsigned e, n;
    unsigned m;
    unsigned p, q;
    unsigned d;
    unsigned totient;

    std::cin
    >> e
    >> n
    >> m;

    unsigned C[m];
    unsigned M[m];

    for (unsigned i = 0; i < m; i++) std::cin >> C[i];

    std::pair<unsigned, unsigned> pq = findpq(n);
    p = pq.first;
    q = pq.second;

    if (p == q || p > q) panic();

    totient = (p - 1) * (q - 1);

    int* triple = gcd(e, totient);

    d = triple[1];

    if (triple[0] != 1) panic();
    
    std::cout << p << ' ' << q << ' ' << totient << ' ' << d << std::endl;

    for (unsigned i = 0; i < m; i++) M[i] = deCrypt(C[i], d, n);

    for (unsigned i = 0; i < m; i++) std::cout << M[i] << ' ';

    std::cout << std::endl;

    for (unsigned i = 0; i < m; i++) std::cout << charize(M[i]);

    delete[] triple;

    return 0;
}

std::pair<unsigned, unsigned> findpq(unsigned n)
{
    unsigned p, q;
    for (p = 2; p <= sqrt(n); p++)
    {
        if (n % p == 0)
        {
            q = n / p;
            if (isPrime(p) && isPrime(q))
            {
                return std::make_pair(p, q);
            }
        }
    }
    panic();
    return std::make_pair(n, 1);
}

bool isPrime(unsigned x) {
    if (x == 0 || x == 1) return false;
    for (unsigned i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0) return false;
    }
    return true;
}

void panic() {
    std::cout << "Public key is not valid!" << std::flush;
    exit(-1);
    return;
}

int* gcd (unsigned a, unsigned b)
{
    int *triple = new int[3];
    if (a == b)
    {
        triple[0] = a;
        triple[1] = 1;
        triple[2] = 0;
        return triple;
    } else if (a > b) {
        triple = gcd(a - b, b);
        triple[2] -= triple[1];
        return triple;
    } else {
        triple = gcd(a, b - a);
        triple[1] -= triple[2];
        return triple;
    }
}

char charize(int x)
{
    if (x == 7)       return 'A';
    else if (x < 33)  return 'A' + x - 7;
    else if (x == 34) return '"';
    else if (x == 35) return ',';
    else if (x == 36) return '.';
    else if (x == 37) return '\'';
    else              return ' ';
}

unsigned deCrypt(unsigned C, unsigned d, unsigned n) {
    if (d == 0) return 1;
    
    unsigned result = deCrypt(C, d / 2, n);
    result = (result * result) % n;
    
    if (d % 2 == 1) result = (result * C) % n;
    
    return result;
}
