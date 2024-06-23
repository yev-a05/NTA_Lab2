#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;


// Функція для перевірки, чи є число генератором
bool is_generator(long long a, long long n) {
    int p = n + 1;
    if (a >= p) return false;

    set<long long> residues;
    long long current = 1;
    for (long long i = 0; i < p - 1; ++i) {
        residues.insert(current);
        current = (current * a) % p;
    }
    return residues.size() == p - 1;
}

// Функція для розкладу числа n на прості множники
vector<pair<int, int>> primeFactorization(int n) {
    vector<pair<int, int>> factors;

    // Розклад на 2
    int count = 0;
    while (n % 2 == 0) {
        count++;
        n /= 2;
    }
    if (count > 0) {
        factors.push_back({ 2, count });
    }

    // Розклад на непарні прості числа
    for (int i = 3; i <= sqrt(n); i += 2) {
        count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) {
            factors.push_back({ i, count });
        }
    }

    // Якщо n - просте число більше 2
    if (n > 2) {
        factors.push_back({ n, 1 });
    }

    return factors;
}

// Функція для обчислення (base^exp) % mod
int modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Функція для обчислення таблиць значень r_{p_i,j}
void computeTables(int n, long long a, const vector<pair<int, int>>& factors) {
    for (const auto& factor : factors) {
        int p = factor.first;
        cout << "Таблиця для p = " << p << ":\n";
        for (int j = 0; j < p; ++j) {
            int r = modExp(a, (n * j) / p, n+1);
            cout << "r(" << p << "," << j << ") = " << r << endl;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    long long n, a, b;

    cout << "Введіть порядок групи n: ";
    cin >> n;

    // Перевірка на генератор a

    while (true) {
        cout << "Введіть генератор a: ";
        cin >> a;

        if (is_generator(a, n)) {
            cout << "Число a є генератором групи Z*_" << n + 1 << ".\n";
            break;
        }
        else {
            cout << "Число a не є генератором. Спробуйте ще раз.\n";
        }
    }

    cout << "Введіть елемент b: ";
    cin >> b;

    vector<pair<int, int>> factors = primeFactorization(n);

    cout << "Канонічний розклад числа " << n << ": ";
    for (size_t i = 0; i < factors.size(); ++i) {
        cout << factors[i].first << "^" << factors[i].second;
        if (i != factors.size() - 1) {
            cout << " · ";
        }
    }
    cout << endl;

    // Обчислення таблиць значень r_{p_i,j}
    computeTables(n, a, factors);

    return 0;
}

