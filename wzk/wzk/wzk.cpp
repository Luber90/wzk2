#include <iostream>
#include <random>
#include <unordered_set>
#include <math.h>

bool isPrime(long n)
{
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}

const long long MOD = 1000000007;

long long fast_power(long long base, long long power) {
    long long result = 1;
    while (power > 0) {

        if (power % 2 == 1) { 
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        power = power / 2; 
    }
    return result;
}

long power(long x, long y, long p)
{
    int res = 1;

    x = x % p;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

void findPrimefactors(std::unordered_set<long>& s, long n)
{
    while (n % 2 == 0)
    {
        s.insert(2);
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
            s.insert(i);
            n = n / i;
        }
    }

    if (n > 2)
        s.insert(n);
}

long findPrimitive(long n)
{
    std::unordered_set<long> s;

    if (isPrime(n) == false)
        return -1;

    int phi = n - 1;

    findPrimefactors(s, phi);

    for (int r = 2; r <= phi; r++)
    {
        bool flag = false;
        for (auto it = s.begin(); it != s.end(); it++)
        {

            if (power(r, phi / (*it), n) == 1)
            {
                flag = true;
                break;
            }
        }

        if (flag == false)
            return r;
    }

    return -1;
}

void dh() {
    long n = 1013;
    long g = findPrimitive(n);
    std::random_device device;
    std::uniform_int_distribution<long long> dist(1, n - 1);
    long Ax = dist(device), X = static_cast<long>(std::pow(static_cast<long double>(g), Ax)) % n;
    std::cout << "A: " << Ax << std::endl;
    long By = dist(device), Y = static_cast<long>(std::pow(static_cast<long double>(g), By)) % n;
    std::cout << "B: " << By << std::endl;
    long Ak = static_cast<long>(std::pow(static_cast<long double>(Y), Ax)) % n, Bk = static_cast<long>(std::pow(static_cast<long double>(X), By)) % n;
    std::cout << Ak << Bk;
}

long long gcd(long long a, long long b) {
    long long c;
    while (b != 0) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

long long mod_inverse(long mianownik, long p) {
    long long i = 1;
    while (true) {
        auto mod = mianownik * i % p;
        if (mod == 1) break;
        i++;
    }
    return i;
}

void rsa() {
    long long p = 5021, q = 5171, n = p * q, phi = (p - 1) * (q - 1);
    std::random_device device;
    std::uniform_int_distribution<long long> dist(2, phi - 1);
    long long e;
    while (true) {
        e = dist(device);
        if (gcd(e, phi) == 1 and isPrime(e)) break;
    }
    long long d = mod_inverse(e, phi);
    std::string msg = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n Nunc eget tempor erat, ac consequat risus.";
    std::vector<long long> ciphered;
    std::string deciphered = "";
    std::cout << "msg: " << msg << std::endl;
    std::cout << "ciphered: ";
    for (auto i : msg) {
        auto element = power(i, e, n);
        ciphered.push_back(element);
        std::cout << element << " ";
    }
    std::cout << std::endl;
    for (auto i : ciphered) {
        deciphered += power(i, d, n);
    }
    std::cout << "deciphered: " << deciphered;
}

int main()
{
    rsa();
}

