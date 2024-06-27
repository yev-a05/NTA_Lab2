#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <windows.h>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
            int r = modExp(a, (n * j) / p, n + 1);
            cout << "r(" << p << "," << j << ") = " << r << endl;
        }
    }
}

// Розширений алгоритм Евкліда для знаходження оберненого елемента
int extendedGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Функція для знаходження оберненого елемента за модулем
int modInverse(int a, int m) {
    int x, y;
    int g = extendedGCD(a, m, x, y);
    if (g != 1) {
        throw invalid_argument("Inverse doesn't exist");
    }
    return (x % m + m) % m;
}

// Функція для обчислення x за допомогою логарифмів mod (p_i)^(l_i)
vector<int> computeXi(int p, int l, int a, int b, int n) {
    int p_i = pow(p, l);
    vector<int> x(l, 0);
    int a_inv = modInverse(a, n + 1);
    int current_b = b;

    for (int k = 0; k < l; ++k) {
        int current = modExp(current_b, n / pow(p, k + 1), n + 1);
        int x_k = 0;

        while (modExp(a, x_k * n / p, n + 1) != current) {
            x_k++;
        }

        x[k] = x_k;
        current_b = (current_b * modExp(a_inv, x_k * pow(p, k), n + 1)) % (n + 1);
    }

    return x;
}

// Функція для обчислення x mod n за допомогою китайської теореми про лишки
int chineseRemainderTheorem(const vector<pair<int, int>>& congruences, int n) {
    int result = 0;
    int N = 1;
    for (const auto& congruence : congruences) {
        N *= congruence.second;
    }

    for (const auto& congruence : congruences) {
        int ai = congruence.first;
        int ni = congruence.second;
        int mi = N / ni;
        int mi_inv = modInverse(mi, ni);
        result = (result + ai * mi * mi_inv) % N;
    }

    return result % n;
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

    auto start_time = high_resolution_clock::now();

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

    // Обчислення x для кожного (p_i)^(l_i)
    vector<pair<int, int>> congruences;
    for (const auto& factor : factors) {
        int p = factor.first;
        int l = factor.second;
        int p_i_l_i = pow(p, l);
        vector<int> x_i = computeXi(p, l, a, b, n);

        // Виведення проміжних значень x_i
        cout << "Для p^l = " << p << "^" << l << " проміжні значення x_i:\n";
        for (int i = 0; i < x_i.size(); ++i) {
            cout << "x_" << i << " = " << x_i[i] << "\n";
        }

        int x_p_i = 0;
        for (int i = 0; i < x_i.size(); ++i) {
            x_p_i += x_i[i] * pow(p, i);
        }

        congruences.push_back({ x_p_i, p_i_l_i });
    }

    // Виведення системи рівнянь
    cout << "Система рівнянь для китайської теореми про лишки:\n";
    for (const auto& congruence : congruences) {
        cout << "x ≡ " << congruence.first << " (mod " << congruence.second << ")\n";
    }

    // Обчислення x mod n за допомогою китайської теореми про лишки
    int x = chineseRemainderTheorem(congruences, n);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();

    cout << "Дискретний логарифм x = " << x << endl;
    cout << "Час виконання програми: " << duration << " мс" << endl;

    return 0;
}











