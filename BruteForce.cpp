// NTA_Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <set>
#include <algorithm>
#include <windows.h>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace chrono;

// Функція для перевірки, чи є число простим
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Функція для перевірки, чи є число генератором
bool is_generator(long long a, long long p) {
    if (a >= p) return false;

    set<long long> residues;
    long long current = 1;
    for (long long i = 0; i < p - 1; ++i) {
        residues.insert(current);
        current = (current * a) % p;
    }
    return residues.size() == p - 1;
}

string format_duration(duration<double> elapsed) {
    auto hrs = duration_cast<hours>(elapsed);
    elapsed -= hrs;
    auto mins = duration_cast<minutes>(elapsed);
    elapsed -= mins;
    auto secs = duration_cast<seconds>(elapsed);
    elapsed -= secs;
    auto millis = duration_cast<milliseconds>(elapsed);
    elapsed -= millis;
    auto micros = duration_cast<microseconds>(elapsed);

    stringstream ss;
    ss << setfill('0') << hrs.count() << ":"
        << setw(2) << mins.count() << ":"
        << setw(2) << secs.count() << "."
        << setw(3) << millis.count()
        << setw(3) << micros.count();
    return ss.str();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    long long p, a, b;

    // Перевірка на простоту числа p
    while (true) {
        cout << "Введіть просте число p: ";
        cin >> p;

        if (is_prime(p)) {
            cout << "Число p є простим числом.\n";
            break;
        }
        else {
            cout << "Число p не є простим. Спробуйте ще раз.\n";
        }
    }

    // Перевірка на генератор a
    while (true) {
        cout << "Введіть генератор a: ";
        cin >> a;

        if (is_generator(a, p)) {
            cout << "Число a є генератором групи Z*_" << p << ".\n";
            break;
        }
        else {
            cout << "Число a не є генератором. Спробуйте ще раз.\n";
        }
    }

    cout << "Введіть елемент b: ";
    cin >> b;

    auto start_time = high_resolution_clock::now();

    // Вектор для зберігання всіх рішень
    vector<long long> solutions;

    // Звичайний перебір для знаходження всіх можливих x
    for (long long x = 0; x <= p - 2; ++x) {
        if (static_cast<long long>(pow(a, x)) % p == b) {
            solutions.push_back(x);
        }
        // Перевірка часу кожну 1000 ітерацій
        if (x % 1000 == 0) {
            auto current_time = high_resolution_clock::now();
            duration<double> elapsed = current_time - start_time;
            if (elapsed.count() > 300) { // 300 секунд = 5 хвилин
                cout << "Програма перевищила обмеження часу (5 хвилин)." << endl;
                return 1;
            }
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = end_time - start_time;

    if (!solutions.empty()) {
        cout << "Знайдені розв'язки: ";
        for (const auto& sol : solutions) {
            cout << endl << "x = " << sol;
        }
        cout << endl;
    }
    else {
        cout << "Розв'язок не знайдено." << endl;
    }

    cout << "Час виконання програми: " << format_duration(duration) << endl;

    return 0;
}*/

