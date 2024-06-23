#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <windows.h>

using namespace std;


// Функція для перевірки, чи є число генератором
bool is_generator(long long a, long long n) {
    int p = n+1;
    if (a >= p) return false;

    set<long long> residues;
    long long current = 1;
    for (long long i = 0; i < p - 1; ++i) {
        residues.insert(current);
        current = (current * a) % p;
    }
    return residues.size() == p - 1;
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
            cout << "Число a є генератором групи Z*_" << n+1 << ".\n";
            break;
        }
        else {
            cout << "Число a не є генератором. Спробуйте ще раз.\n";
        }
    }

    cout << "Введіть елемент b: ";
    cin >> b;


    return 0;
}